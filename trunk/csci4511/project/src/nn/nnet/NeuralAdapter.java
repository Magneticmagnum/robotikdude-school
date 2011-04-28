package nn.nnet;

import nrlibj.NNet;

/**
 * Neural adapter class to easily instantiate a neural network with either >= 0
 * hidden layer neurons
 * 
 * @author Joe Houlton (C) Apr 28, 2011
 */
public class NeuralAdapter {

	private NNet network;

	/**
	 * Create a neural adapter with no hidden layer (perceptron)
	 * 
	 * @param inputNodes
	 * @param outputNodes
	 */
	public NeuralAdapter(int inputNodes, int outputNodes) {
		// TODO Auto-generated constructor stub
		network = new NNet("layer=0 tnode=" + inputNodes + " nname=NodeLin "
				+ "layer=1 tnode=" + outputNodes + " nname=NodeLin "
				+ "link=all fromLayer=0 toLayer=1");
	}

	/**
	 * Create a neural adapter with a hidden layer, w/ sigmoid activation func
	 * 
	 * @param inputNodes
	 * @param hidden
	 * @param outputNodes
	 */
	public NeuralAdapter(int inputNodes, int hidden, int outputNodes) {
		network = new NNet("layer=0 tnode=" + inputNodes + " nname=NodeLin "
				+ "layer=1 tnode=" + hidden + " nname=NodeSigm "
				+ "layer=2 tnode=" + outputNodes + " nname=NodeLin");
	}

	/**
	 * Run the neural network on the input, no learning occurs
	 * 
	 * @param parameters
	 * @return
	 */
	public float[] solution(float[] parameters) {
		float[] out = new float[parameters.length];
		network.frwNNet(parameters, out);
		return out;
	}

	/**
	 * Train the neural network on the input and expected value returns what it
	 * recognized
	 * 
	 * @param input
	 * @param expected
	 * @return
	 */
	public float[] train(float[] input, float[] expected) {
		float[] out = new float[input.length];
		network.ebplrnNNet(input, out, expected);
		return expected;
	}
}
