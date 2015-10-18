__author__ = 'Joey Bronner'

# Imported libraries
import json
import sys
import urllib2
import time
import serial

# Configurations
arduino = serial.Serial('COM3', 9600)

# Global variables
SUCCESS = 's'
FAILURE = 'f'
BUILDING = 'b'
UNSTABLE = 'u'
JENKINS_START_URL = 'http://dewdflhana1265.emea.global.corp.sap:8080/job/'
JENKINS_END_URL = '/lastBuild/api/json'
JOBS = ['build-sbi-ui-master']

print '---------- JENKINS LIGHTER ----------'
print 'Developer: Joey Bronner'
print 'Email    : joey.bronner@sap.com'
print '-------------------------------------'


def get_status(jobName):
    try:
        stream = urllib2.urlopen(JENKINS_START_URL + jobName + JENKINS_END_URL)
    except urllib2.HTTPError, e:
        print 'URL Error: ' + str(e.code)
        sys.exit(2)
    try:
        buildStatus = json.load(stream)
    except:
        print "Failed to parse json"
        sys.exit(3)
    return jobName, buildStatus["timestamp"], buildStatus["result"],

while(1):
    for job in JOBS:
        status = get_status(job)
        print status[0], status[1], status[2]
        if status[2] == "UNSTABLE":
            arduino.write(UNSTABLE)
        elif status[2] == "SUCCESS":
            arduino.write(SUCCESS)
        elif status[2] == "FAILURE":
            arduino.write(FAILURE)
        elif status[2] == "BUILDING":
            arduino.write(BUILDING)
        elif status[2] == None:
            arduino.write(BUILDING)

        # Waiting time before to loop
        time.sleep(2)
