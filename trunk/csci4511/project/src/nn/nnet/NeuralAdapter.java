package nn.nnet;

import nn.matrices.Vector;

/**
 * Neural adapter class to easily instantiate a neural network with either >= 0
 * hidden layer neurons
 * 
 * @author Joe Houlton (C) Apr 28, 2011
 */
public class NeuralAdapter {

	private NeuralNetwork net;

	/**
	 * Create a neural adapter with no hidden layer (perceptron)
	 * 
	 * @param inputNodes
	 * @param outputNodes
	 */
	public NeuralAdapter(int inputNodes, int outputNodes) {
		net = NeuralNetwork.create(inputNodes, outputNodes);
	}

	/**
	 * Create a neural adapter with a hidden layer, w/ sigmoid activation func
	 * 
	 * @param inputNodes
	 * @param hidden
	 * @param outputNodes
	 */
	public NeuralAdapter(int inputNodes, int hiddenNodes, int outputNodes) {
		net = NeuralNetwork.create(inputNodes, hiddenNodes, outputNodes);
	}

	/**
	 * Run the neural network on the input, no learning occurs
	 * 
	 * @param parameters
	 * @return
	 */
	public double[] solution(double[] parameters) {
		Vector dblVec = new Vector(parameters);
		Vector out = net.get(dblVec);
		double[] arr = new double[out.getLength()];
		out.values(arr);
		return arr;
	}

	/**
	 * Train the neural network on the input and expected value returns what it
	 * recognized
	 * 
	 * @param input
	 * @param expected
	 * @return
	 */
	public int train(double[] inp, double[] expected) {
		return train(inp, expected, 1);
	}

	public int train(double[] inp, double[] exp, double alpha) {
		Vector input = new Vector(inp);
		Vector output = new Vector(exp);
		return net.train(input, output, alpha);
	}
}
