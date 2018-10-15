# Project 1.5  
Code written by: [vmangs](https://github.com/vmangs)
### Give me a bullet-point list of specific weaknesses you found.
* ERR51-CPP. Handle all exceptions
* STR53-CPP. Range check element access
* FIO51-CPP. Close files when they are no longer needed
* MSC50-CPP. Do not use std::rand() for generating pseudorandom numbers
* MSC51-CPP. Ensure your random number generator is properly seeded
### For each weakness give your best one-sentence advice for how to resolve the issue before release.
#### This includes a detailed explanation and solution for each vulnerability.
* ERR51-CPP:  
The code below does not handle exceptions. No exception handling can cause unintended errors to occur.  
	```
	ifstream fileinput;
	fileinput.open(filename.c_str());
	```
	The code above can be improve like below:
	```
	ifstream fileinput;
	fileinput.exceptions(ifstream::badbit);
  	try {
    	fileinput.open(filename.c_str());
    	// Task
  	} catch (const ifstream::failure& e) {
    	// Error handling
  	}
	```

* STR53-CPP:  
The code below doesn't check whether the index is within range that the string can handle.
	```
	firststring = wordlist[firststring].at(rand() % wordlist[firststring].size());
	```
	The code above can be improve like below:
	```
	try {
    	firststring = wordlist[firststring].at(rand() % wordlist[firststring].size());
	} catch (std::out_of_range &) {
    	// Error handling
  	}
  	```  
  	This solves the issue in case `wordlist[firststring]` is null and when `wordlist[firststring].at(rand() % wordlist[firststring].size())` is out of range.

* FIO51-CPP:  
The method `fileIntoWordList` does not close the file it used once it finished reading it.  
This can be fixed by adding `fileinput.close();` to the end of the function.

* MSC50-CPP:  
`std::rand()` is good for testing, but is not so random.  
With some information such as sequence generated by the `std::rand()` function as well as the index of the generated numbers could let one to predict the following randomly generated numbers.  
It is recommended to use other algorithms such as the [Mersenne Twister](http://dl.acm.org/citation.cfm?doid=272991.272995) algorithm.
	```
	#include <random>
	#include <string>
  	
	void f() {
  		std::string id("ID"); // Holds the ID, starting with the characters "ID" followed
                        // by a random integer in the range [0-10000].
  		std::uniform_int_distribution<int> distribution(0, 10000);
  		std::random_device rd;
  		std::mt19937 engine(rd());
  		id += std::to_string(distribution(engine));
  		// Code required for the function
	}
	```

* MSC51-CPP:  
Using `srand(time(NULL));` as the seed allow attackers to predict PRNG since the attackers would be able to control the time.  
The example solution above also solves this issue by using `std::random_device rd;` in its code base.
		
### Give short general guidance for the developers.
PRNGs are not really random. Make sure you safer algorithms rather than the easy to implement algorithm.  
Be wary whenever allocating memory. Whenever allocating, there should be a destructor.  
Exception handling is a must to prevent unexpected errors.  
Release resource after finished using it or else it can cause dead locks and many other terrible things to happen.
### How many hours did you spend on this?
	About 4 hours?
### Tell me about any "a-ha" moments or insights.
I didn't expect to see information regarding PRNGs in the CERT webpage. It reminded me that you taught us that PRNGs aren't really random. `rand()` could be good for testing purposes, but shouldn't be used in real practice.
### Can you put this report in your portfolio? If not, why not?
I think it can be somewhat used in my portfolio. If I did a report for my own code, I think it would be way more of a worthy report to be in my portfolio. The code I reviewed utilized `stl::string` so I was not able to check through many of the memory allocation and dealloation rules for CERT. My project instead uses C so I had to code every single bit from scratch. This led me to write quick code rather than secure code. I didn't write destructors and occasionally accessed memory that I shouldn't be accessing. That project would had way more juicy content to review.