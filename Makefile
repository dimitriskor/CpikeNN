GCC=g++

exe: test.o gradient.o neuron.o SNN_class.o STDP.o WFSP.o
	$(GCC) test.o gradient.o neuron.o SNN_class.o STDP.o WFSP.o -o exe

test.o: test.cpp gradient.h neuron.h SNN_class.h STDP.h WFSP.h
	$(GCC) -c test.cpp

gradient.o: gradient.cpp neuron.h gradient.h SNN_class.h
	$(GCC) -c gradient.cpp

neuron.o: neuron.cpp neuron.h
	$(GCC) -c neuron.cpp

SNN_class.o: SNN_class.cpp SNN_class.h neuron.h STDP.h gradient.h
	$(GCC) -c SNN_class.cpp

STDP.o: STDP.cpp STDP.h neuron.h SNN_class.h
	$(GCC) -c STDP.cpp

WFSP.o: WFSP.cpp WFSP.h neuron.h SNN_class.h
	$(GCC) -c WFSP.cpp

clear:
	rm *.o exe
