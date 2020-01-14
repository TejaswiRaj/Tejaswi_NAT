
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
Improvement opportunities:
* In the list, the first entries ended up as null elements. Instead of fixing it, due to time constraints I've skipped the entry through an 'if' condition.
* The destination IP string could be stored in a list instead of a map, to optimize space.
* The search operation can be optimized further to avoid repeated comparison with earlier elements
* The validity of the IP address and port address not checked -> i.e, if the values are beyond 255 or port value is beyond 16 bits, it will be accepted in this code now.
* The input order of the FLOW list is not maintained.
* Further code optimization and exception handling can be done
* Assumed the input files to be local. They are not passed through arguments.
================================================================================
Tested with the provided sample NAT, sample FLOW files along with some error cases.

Input

The inputs to the program should be two files; NAT and FLOW.

The NAT file will describe the translations for your NAT Table. The format of each line will be as so:
<ip>:<port>,<ip>:<port>

The first ip, port pair is original ip and port that should be translated to the second ip, port pair. The ip or the port (not both) can have a “*” instead of an ip or port. The star means that anything should match that value. For example, the following are all valid inputs:

10.0.1.1:8080,192.168.0.1:80
*:8081,192.168.0.1:80
10.0.1.2:*192.168.0.1:80

The FLOW file will describe the incoming flows through your NAT. The format of each line will be as so
<ip>:<port>

The ip,port pair is the incoming flow that may or may not be modified by your NAT. There cannot be a “*” in the input for the flow. For example, the following is a valid input

192.168.0.1:8081

Output

The output to your program should be one file; OUTPUT.

The ouput file should have one entry corresponding to each line in the FLOW file. If there is a match, that line should output the original ip, port pair and the translated ip, port pair. If there is no match, the program should output that there is no NAT entry for that ip, port pair.

You may assume that the input file contains only valid, well-formed entries. A sample input NAT and FLOW file as well as the corresponding sample output for those two inputs are below.

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

================================================================================


