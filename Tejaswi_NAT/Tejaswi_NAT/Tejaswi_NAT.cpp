//#include "pch.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

multimap<string, string> firstip;// source ip address and port from NAT file
multimap<string, string> natmap; // both src and dest ip from NAT file 
multimap<string, string> flowIPmap; // ip address and port from FLOW file

class NAT
{
private: fstream outfile;

public:

	void parseNAT(string str)
	{
		int srcLen = str.find(','); // error handling later
		string src_adr = str.substr(0, srcLen); // get the src IP and port (till the first ',')
		int p = src_adr.find(':'); // split IP address and port number 
		string srcip = src_adr.substr(0, p); // assign the 1st ip address
		string srcPort = src_adr.substr(p + 1); // assign the 1st port num
		// Check if both srcip and srcPort are "*"
		if ((srcip == "*") && (srcPort == "*")) { // error case
			cout << "not a valid input for NAT address" << endl;
			return;
		}
		firstip.insert(std::pair<string, string>(srcip, srcPort));
		string dest_adr = str.substr(srcLen + 1); // second address and port of the NAT line
		natmap.insert(std::pair<string, string>(src_adr, dest_adr)); // add src and dest to natmap
	}
	/* ========================================================================================
	*/
	void parseFLOW(string str)
	{
		int iplen = str.find(':');
		string flow_ip = str.substr(0, iplen);  //Get the ip address
		string flow_port = str.substr(iplen + 1); // port number part of the line
		if ((flow_ip == "*") || (flow_port == "*")) { // Check if flow_ip does not have a *
			cout << "not a valid input for Flow address" << endl;
			return;
		}
		flowIPmap.insert(std::pair<string, string>(flow_ip, flow_port)); // add ip and port to flowIPmap
	}
	/* ====================================================================================================
	*/
	void CheckRoute(multimap<string, string>& fst, multimap<string, string>& flowIP, multimap<string, string>& nat)
	{
		multimap<string, string>::iterator i, j, k;
		bool found = false;
		outfile.open("OUTPUT.txt", ios::out | ios::trunc);

		for (j = flowIP.begin(); j != flowIP.end(); j++, found = false) // iterate through FLOW entries
		{
			if (j->first == "") continue; // First enty is NULL. Will solve it later.
			string ipVal = j->first;    // pick IP address
			string portNum = j->second; // store port num

			for (i = fst.begin(), k = nat.begin(); i != fst.end(); i++, k++) // iterate through the src addresses for comparison
			{
				if (i->first == "") continue;
				if ((i->first == ipVal) || (i->first == "*")) {// src IP can be a "*" or an exact match
					// Note: Both i->first and i->second can't be "*" by design -> refer to the parse function
					if ((i->second == portNum) || (i->second == "*")) {  // if port also matches or is a "*", it's a success. 
						outfile << j->first << ":" << j->second << " -> " << k->second << endl; // Print the mapping
						found = true;
						break;
					}
				}
			}
			if (found == false)
				outfile << "No nat match for " << j->first << ":" << j->second << endl;
		}
		outfile.close();
	}
};
/*==============================================================================================
*/
int main()
{
	NAT natObj;
	ifstream natFile;
	ifstream flowFile;
	string natStore;
	string flowStore;

	// ============== Handle NAT file ===================
	natFile.open("NAT.txt");
	if (!natFile.is_open()) {
		cout << "NAT.txt file not available in the local folder" << endl;
		return -1;
	}

	while (!natFile.eof())
	{
		getline(natFile, natStore); // Stores the lines of NAT file
		natObj.parseNAT(natStore);   // Parsing and processing of the NAT lines
	}
	natFile.close();

	// ============== Handle FLOW file ===================
	flowFile.open("FLOW.txt");
	if (!flowFile.is_open()) {
		cout << "FLOW.txt file not available in the local folder" << endl;
		return -1;
	}

	while (!flowFile.eof())
	{
		getline(flowFile, flowStore); // store each line
		natObj.parseFLOW(flowStore);  // Parse the addresses
	}
	flowFile.close();

	// ============== Process the Routing ===================
	natObj.CheckRoute(firstip, flowIPmap, natmap); // Search for the FLOW entries in the NAT file

	return 0;
}