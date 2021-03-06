// NN1of3.cpp : Defines the entry point for the console application.
//

/*

	Basic neural net, adapted from: https://medium.com/technology-invention-and-more/how-to-build-a-simple-neural-network-in-9-lines-of-python-code-cc8f23647ca1
	Created in an effort to learn how neural networks function and how to create them, adapted from python in above article

*/



#include "stdafx.h"
#include <cstdlib>	//for random and RAND_MAX
#include <math.h>	//for exp
#include <iostream>
using namespace std;

//Class meant to model a network with 3 input nodes and one ouput node
class NeuralNetwork {

	float weights[3];	//represents weights of synaptic connections between input layer and output neuron
	float output;		//holds output value
	float error;		//holds error value

	//used to bound generation of random values for weight initialization, weights are initialized to values between -1 and 1 
	const int LO = -1;
	const int HI = 1;

public:
	NeuralNetwork() {

		//randomly assign weights. Formula from: https://stackoverflow.com/questions/686353/c-random-float-number-generation by John Dibling
		//Assign random float val between LO and HI: 
		//LO + static_cast <float> (rand()) /( static_cast <float> (RAND_MAX/(HI-LO)))
		for (int i = 0; i < 3; i++) {

			weights[i] = LO + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (HI - LO)));

		}

	}

	float sigmoid(float x) {	// 1/(1+e^(-x)) uses sigmoid function to normalize value between 0 and 1

		return 1 / (1 + (exp(-x)));

	}

	float deriv(float x) {	//x * (1-x) is derivative of the sigmoid function, used to calculate gradient at this point in the solution space and adjust accordingly during backpropogation

		return x * (1 - x);

	}

	float think(float in[3]) {

		float out = 0;
		for (int i = 0; i < 3; i++) {	//calculate weighted sum of inputs to find output

			out += in[i] * weights[i];

		}

		return sigmoid(out);	//normalize output value between 0 and 1

	}

	void train(float in[4][3], float out[4], int timesToTrain) {

		for (int i = 0; i < timesToTrain; i++) {	//train NN timesToTrain amount of times

			for (int l = 0; l < 4; l++) {	//load all training data from input argument


				/*cout << "Weights in trial #" << (l + 1) << endl;
				for (int g = 0; g < 3; g++) cout << weights[g] << " | ";
				cout << endl;
				*/

				output = think(in[l]);	//calculate output of output neuron

				error = out[l] - output;	//calculate difference between expected and actual output
				
				for (int k = 0; k < 3; k++) {	//backpropogates, changes weights based on error and gradient

					weights[k] += error * in[l][k] * deriv(output);

				}

			}

		}

		/*cout << "Final weights: " << endl;
		for (int i = 0; i < 3; i++) cout << weights[i] << " | ";
		cout << endl;
		*/
		cout << "Final error: " << error << endl;
	}

};

int main()
{

	NeuralNetwork testNet = NeuralNetwork();

	float in[4][3];
	in[0][0] = 0; in[0][1] = 0; in[0][2] = 1;
	in[1][0] = 1; in[1][1] = 1; in[1][2] = 1;
	in[2][0] = 1; in[2][1] = 0; in[2][2] = 1;
	in[3][0] = 0; in[3][1] = 1; in[3][2] = 1;

	float out[4];
	out[0] = 0;
	out[1] = 1;
	out[2] = 1;
	out[3] = 0;

	testNet.train(in,out,10000);

	cout << endl;

	for (int i = 0; i < 4; i++) {

		cout << "Test #" << (i + 1) << ": ";
		cout << testNet.think(in[i]) << endl;

	}


	float test[3];

	cout << "Input: " << endl;

	for (int i = 0; i < 3; i++) cin >> test[i];

	cout << "Thought: " << testNet.think(test) << endl;










    return 0;
}

