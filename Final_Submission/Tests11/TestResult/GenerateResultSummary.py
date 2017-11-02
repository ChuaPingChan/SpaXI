
import sys
import os
import xml.etree.ElementTree as ET

#CURRENT_WORKING_DIRECTORY = os.getcwd()
CURRENT_WORKING_DIRECTORY = sys.argv[1]
OUTPUT_PATH = sys.argv[2]

def main():
	overallTestRan = 0
	overallNumPass = 0;
	overallNumFail = 0;
	overallTimeout = 0;
	overallSummary = '';
	summary = ''
	
	for root, dirs, files in os.walk(CURRENT_WORKING_DIRECTORY, topdown=False):
		for name in files:
			filePath = os.path.join(root, name)
			ext = os.path.splitext(filePath)[-1].lower()
			if (ext == '.xml'):
				numTotalTestRanForThisFile = 0;
				numPassForThisFile = 0
				numFailForThisFile = 0;
				numTimeoutForThisFile = 0;
				tree = ET.parse(filePath)
				data = tree.getroot()
				for elem in data.iter():
					if (elem.tag == 'passed'):
						numTotalTestRanForThisFile += 1
						numPassForThisFile += 1
					elif (elem.tag == 'failed'):
						numTotalTestRanForThisFile += 1
						numFailForThisFile += 1
					elif (elem.tag == 'timeout'):
						numTotalTestRanForThisFile += 1
						numTimeoutForThisFile += 1

				summary += filePath + ': \n'
				if numFailForThisFile is 0:
					summary += 'Test Ran: ' + str(numTotalTestRanForThisFile) +'\n'
				else:
					summary += 'Test Ran: ' + str(numTotalTestRanForThisFile) + '	[BUG]' +'\n'
				summary += 'Passed   : ' + str(numPassForThisFile) + '\n'
				summary += 'Failed   : ' + str(numFailForThisFile) + '\n'
				summary += 'Timeout  : ' + str(numTimeoutForThisFile) + '\n'
				summary += '\n'
				overallTestRan += numTotalTestRanForThisFile
				overallNumPass += numPassForThisFile
				overallNumFail += numFailForThisFile
				overallTimeout += numTimeoutForThisFile
				
	overallSummary += 'Overall Test Ran    : ' + str(overallTestRan) + '\n'
	overallSummary += 'Overall Test Passed : ' + str(overallNumPass) + '\n'
	overallSummary += 'Overall Test Failed : ' + str(overallNumFail) + '\n'
	overallSummary += 'Overall Test Timeout: ' + str(overallTimeout) + '\n'
	overallSummary += '\n\n'
	overallSummary += summary
	
	outputAsNewFile(overallSummary, OUTPUT_PATH)

def outputAsNewFile(data, destinationPath):
	with open(destinationPath, 'w') as ofp:
		ofp.write(data)

if __name__ == "__main__":
	main()
