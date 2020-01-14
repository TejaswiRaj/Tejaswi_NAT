Tested on Visual Studio 17 (Windows 10) and g++ (Ubuntu)

Tejaswi_NAT.cpp is the only file used as part of the visual studio solution
The input and output files are placed locally in the same folder.
================================================================================
Overall approach:

Parse and store NAT file
	Input has source and destination IP:port pairs
	Parsing constraint: Either IP or port may be '*' but not both; Destination is taken as is.
	[validation constraint: IP byte value, port max limit - not done now]
Parse and store FLOW file
	Each line should be an IP:port pair
	
Algorithm:	
For each entry in the FLOW, do the following:
	Search for the IP or '*' in the NAT input list
		If there is a match, check the port or '*'
		If success, print the line "<FLOW IP:port> -> <destination IP:port>" to output
	If no match, print "No nat match for " IP:port
done
================================================================================
With the same set of input lines in the NAT and FLOW, along with some additional error conditions I have tested the outputs.

Improvement opportunities:
* In the list, the first entries ended up as null elements. Instead of fixing it, due to time constraints I've skipped the entry through an 'if' condition.
* The search operation can be optimized further to avoid repeated comparison with earlier elements
* The validity of the IP address and port address not checked -> i.e, if the values are beyond 255 or port value is beyond 16 bits, it will be accepted in this code now.
* The input order of the FLOW list is not maintained.
* Further code optimization and exception handling can be done
* Assumed the input files to be local. They are not passed through arguments.
================================================================================

