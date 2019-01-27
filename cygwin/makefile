
all:
	make 08
	make 09
	#make 10
	#make 11
	make configurationFactor
	make configurationFactor00
	make eigenvalues
	make eigenvalues__01
	make improveA
	make simexp
	#make SinglePendulum
	make TestArrays
	make TestDiffusion1d
	make TestDiffusion2d
	make TestLA
	make TestLA01
	make TestLA02
	make TestLA03
	#make TestLQR
	#make TestMathFunction
	#make TestMathTensor1
	#make TestMathTensor2
	#make TestMathTerm
	make TestODE
	make TestPoisson1d
	make TestRandom
	./TestRandom
	#make run_eigenvalues
	#./eigenvalues__01 eigenvalues.txt
	#make run_improveA

%: %.cpp
	g++ $< -o $@

run_%:
	./$* $*.txt

clean:
	rm -f *.obj
	rm -f *.exe

