GCC=g++

exe: test.o gradient.o neuron.o SNN_class.o STDP.o WFSP.o Layer.o
	$(GCC) test.o gradient.o neuron.o SNN_class.o STDP.o WFSP.o Layer.o -o exe

test.o: test.cpp gradient.h neuron.h SNN_class.h STDP.h WFSP.h Layer.h
	$(GCC) -c test.cpp

gradient.o: gradient.cpp neuron.h gradient.h SNN_class.h Layer.h
	$(GCC) -c gradient.cpp

neuron.o: neuron.cpp neuron.h
	$(GCC) -c neuron.cpp

SNN_class.o: SNN_class.cpp SNN_class.h neuron.h STDP.h gradient.h Layer.h
	$(GCC) -c SNN_class.cpp

STDP.o: STDP.cpp STDP.h neuron.h SNN_class.h Layer.h
	$(GCC) -c STDP.cpp

WFSP.o: WFSP.cpp WFSP.h neuron.h SNN_class.h Layer.h
	$(GCC) -c WFSP.cpp

Layer.o: Layer.cpp Layer.h neuron.h
	$(GCC) -c Layer.cpp

clear:
	rm *.o exe
