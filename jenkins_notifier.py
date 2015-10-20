__author__ = 'Joey Bronner'

# TODO : Launch this python script using a bat file or another think like this
# TODO : ???

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
    # Perform Jenkins global job URL
    try:
        stream = urllib2.urlopen(JENKINS_START_URL + jobName + JENKINS_END_URL)
    except urllib2.HTTPError, e:
        print 'Error: Problem with URL, ' + str(e.code)
        sys.exit(2)

    # Parse response for global job URL
    try:
        buildStatus = json.load(stream)
    except:
        print "Error: Failed to parse JSON file"
        sys.exit(3)
    return jobName, buildStatus["timestamp"], buildStatus["result"], buildStatus["comment"], buildStatus["displayName"],

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