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
Sample Inputs

NAT File
10.0.1.1:8080,192.168.0.1:80

10.0.1.1:8084,192.168.0.2:8080

10.0.1.1:8086,192.168.0.4:80

10.0.1.1:8082,192.168.0.3:80

10.0.1.2:8080,1.1.1.1:1

*:21,1.2.3.4:12

10.11.12.13:*,40.100.20.7:3389

 

FLOW File 
10.0.1.1:8080

5.6.7.8:55555

10.0.1.1:8086

9.8.7.6:21

10.1.1.2:8080

34.65.12.9:22

10.0.1.2:8080

 

Sample Output

10.0.1.1:8080 -> 192.168.0.1:80

No nat match for 5.6.7.8:55555

10.0.1.1:8086 -> 192.168.0.4:80

9.8.7.6:21 -> 1.2.3.4:12

No nat match for 10.1.1.2:8080

No nat match for 34.65.12.9:22

10.0.1.2:8080 -> 1.1.1.1:1
 
 ==============================================================================

Improvement opportunities:
* In the list, the first entries ended up as null elements. Instead of fixing it, due to time constraints I've skipped the entry through an 'if' condition.
* The search operation can be optimized further to avoid repeated comparison with earlier elements
* The validity of the IP address and port address not checked -> i.e, if the values are beyond 255 or port value is beyond 16 bits, it will be accepted in this code now.
* The input order of the FLOW list is not maintained.
* Further code optimization and exception handling can be done
* Assumed the input files to be local. They are not passed through arguments.
================================================================================

