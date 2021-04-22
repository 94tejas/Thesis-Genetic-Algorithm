# Thesis-Genetic-Algorithm
---

## Introduction:

The idea that some biological processes might operate on quantum mechanical laws has been
around for about a century. Recent studies in the past few decades have indicated a possible link between some biological
processes and Quantum Physics. Quantum mechanical processes are believed to be the
working force underlying some biological processes like Photosynthesis, charge transfer in DNA
and Cellular Respiration. The impressive navigational ability of the migratory birds like the
Robin are also shown to be derived from quantum mechanical processes undergoing in the
bird’s retina. Experiments with European Robins have showed that the navigational ability of the bird is
dependent on the local geomagnetic field. Avian magnetoreception is the ability of migratory birds to sense the geomagnetic field for navigation. This mechanism of sensing the geomagnetic field is called as the ‘Avian Compass’. 

A bird’s retina is believed to contain photoreceptor pigments (like cryptochrome), aligned along the curvature of the retina, with
varying molecular axis directions. When light is incident on the retina, electron transfer takes
place between adjacent pigments in the retina. This polarization leads to the formation of
radical pairs (pair of charged molecules) with each molecule having an electron with unpaired
spin. Under the influence of the geomagnetic field, the spins undergo either singlet or triplet
transitions. The radical pairs formed are short-lived (lifetime of order of microseconds) and
recombine to form singlet chemical product and triplet chemical product based on their spin
states. The coherence time is estimated to be in the order of microseconds. The amount of the
chemical product formed varies along the curvature of the retina and is dependent on the
geomagnetic field and the molecular axis orientation. This information of the varying chemical
product in the bird’s retina is transferred to the bird’s brain and it processes the information to
correlate with the geomagnetic field. Thus, the profile of the local geomagnetic field is
transferred to the bird’s brain in the form of profile of varying amount of chemicals formed.
This process has a coherence time of the order of microseconds. This results in the bird getting
a sense of direction repeatedly.


A quantum mechanical model is proposed for this avian compass. The spin of the electron is coupled with the spin of its nucleus and the spin of the other
electron in the radical pair. A study has shown that the spin of one of the electrons in the
radical pair is effectively uncoupled from that of any other particle and is only dependent on
the geomagnetic field. The sensitivity of this avian compass is calculated as the difference of the singlet
product yield between the ends of the field of vision of the bird. The higher the sensitivity,
better is the navigational ability. This sensitivity is dependent on variables like the hyperfine
tensor, the recombination rate of radical pairs and the initial state of the system.
The Hamiltonian of this model assumes the hyperfine tensor components and other elements like the initial state of the spins and the recombination rate.
This project aims to optimize the sensitivity of this Avian compass with respect to the components of the hyperfine tensor by using Genetic algorithm.

Since the hyperfine tensor has 3 components, traditional optimization algorithms would be inefficient and may give the wrong answer. Genetic
algorithms are used for this purpose. They generate random solution space, calculate the
sensitivity for each one of the possible solutions, choose the most promising solutions as the
next solution space. This procedure is repeated as many times as required to reach a tentative
solution. Genetic algorithms imitate the nature’s process of evolution, by making constant
improvements over many generations. They may not provide the best possible solution, but
they provide many good solutions for the problem

---

## Genetic Algorithm:

Genetic algorithms are optimization algorithms used for optimizing functions with multiple
variables. They are different than traditional approach to optimization which involves varying
the value of the variables linearly, moving in one direction, generating data for the entire range
and then finding the global maximum (minimum). For functions having more than 2 variables, it
becomes a time consuming and computationally expensive task when using traditional
algorithms. Genetic algorithms work in a different manner by generating random sets of
possible solution values which span across the entire permitted range, and then moving
towards the more promising solutions and disregarding the solutions which are farther away
from the optimum value.

Genetic algorithms are inspired from the natural evolution process. In nature, in every
generation of a species, the part of the population with better survival traits have a higher
tendency to mate and higher chance of passing their traits to the next generation. Therefore,
every generation is on average better than the previous generation. Genetic algorithms use this
principle to move towards the optimum solution generation by generation. Genetic algorithms
do not necessarily always give the best possible solution, but they provide a small number of
good solutions.

The terminology used in genetic algorithms is explained below -

**Population**: The solution space at any given point of time

**Phenotype**: Population in real world solution space

**Genotype**: Population in computational space

**Chromosome**: An element of the population

**Gene**: An element position in the chromosome

**Allele**: Possible value a gene can take

**Generation**: each stage of population

**Fitness Function**: function to be optimized


![Genetic Algo flowchart](/flow.png)


---

### Encoding 

The encoding of our current sensitivity optimization problem is as follows -

**Fitness function**: Sensitivity (Δs)
**Variables**: Components of the Hyperfine tensor (Ax, Ay, Az)
**Population**: Variable (usually taken 10^5)
**Phenotype**: Range of each variable is of the order of 10 5 to 10 8
**Genotype**: Binary representation of each variable
**Chromosome**: 30 bytes long character string (10 bytes for each variable)
**Allele**: Character ‘0’ or ‘1’

---

### Crossover Mutation

Crossover functions are analogous to mating in natural evolution. They allow chromosomes
with higher fitness function values to mate and produce children which have a higher chance of
giving a higher fitness value. Crossover takes place between two chromosome of the same
population. When the genotype is binary representation, there are multiple ways of
implementing the crossover function like,

- One-point crossover: The binary string is broken down at a fixed point and the one half
of a chromosome is swapped with the corresponding half portion of the second
chromosome.

- Two-point crossover: The binary string is divided at 2 points in the string and the
portions at the end are swapped with corresponding portions of the second string.

- Uniform crossover: Each child is formed gene by gene by taking the corresponding gene
from one of the parents. The probability for a particular gene to be taken from a parent
is 50%.

---

### Mutation Function

In natural evolution, mutation takes place with low probability in a generation. Its purpose is to
introduce diversity in the population with the hope of that diversity leading to a better breed
with higher survival chances. Mutation in genetic algorithms works in the same way and serves
the same purpose i.e. introducing diversity. The probability of mutation happening in a
generation is usually kept low at around 1-5% so as to not steer the population away from the
optimum solution’s path. When the genotype is binary, mutation can be implemented as-

- Bit flip operation: Randomly flip the bits of random chromosomes in a population
- Bit swap: Swap the bits on random positions in a chromosome

---

### Survival Selection

This step involves choosing the parts of the population to promote to the next generation and
the parts to discard entirely. This step has a major effect on the performance of the genetic
algorithm. Selection of chromosomes can be done in two ways: Age-based selection or Fitness-
based selection methods. In age-based selection method, the number of generations for which
a chromosome has been in the population is the deciding factor. If it is greater than a fixed
number, then it discarded. In fitness based selection, higher the fitness value higher is the
chance of being promoted to the next generation. Fitness based selection methods consist of
probabilistic methods like Roulette-wheel selection method or tournament selection method.

---

### Termination Condition

Termination condition can be when a fixed value of the objective is reached or a fixed number
of generations have passed or the current population size is lower than a certain number or
there is no or little improvement in the solutions generated over the past few generations

---

## Problem specific conditions


Choosing the appropriate function to use for crossover, mutation, survival selection, etc.
is all based on the specific details of the problem. There is a lot of flexibility in implementing the
functions mentioned above. The functions should be tailored to the problem. The more
problem-specific knowledge is fed into the algorithm, the better it performs and sooner it
converges to the optimum solution. Effective implementation of genetic algorithms is all about
balancing the diversity in the population with problem-specific knowledge. If the diversity is
kept low, the algorithm has a high chance of converging at the nearest local optimum.
Crossover and mutation help in maintaining diversity in the population.

For this particular problem of optimizing sensitivity, I am using two-point crossover
function applied for each variable individually. The mutation function is a bit flip function which
has a 5-10% probability of occurring in a generation. For the survival selection function, I tried
many methods like roulette wheel selection method and tournament selection method. The
lack of problem specific knowledge in this case, led to failure of these methods to converge at a
point. Therefore, I choose to select top 40% of the population with highest fitness value and
bottom 10% of the population (with lowest fitness value) for the next generation and discarded
the 50% of the population left. The bottom 10% was kept to maintain diversity. Thus, the
population is reduced to half its number after every generation. This led to a steady increase in
the average fitness value of each generation and the algorithm converged to a point. The
termination condition was kept at when the population size was reduced to less than 10.

---

## Implementation


The C++ library linear algebra ['Eigen'](http://eigen.tuxfamily.org/index.php?title=Main_Page) has been used for calculation of the eigenvalues and eigenvectors of the Hamiltonian. Eigen library is useful for performing large matrix operations.

The GCC compiler (version 4.4 or higher) is required for compilation. The command used for compilation is,

`g++ -std=c++11 main.cpp -o output_filename`

The results are stored in ‘output.txt’ in the same folder as the main.cpp file. To plot the
Sensitivity vs. Theta plot compile and run the ‘phi_vs_theta.cpp’ file in the same manner as
above. Enter the values of (Ax, Ay, Az) obtained in output.txt as input. The output of this
program is stored in ‘phiS.txt’.

‘gnuplot’ software has been used to plot all the graphs. The file ‘printGraphs.p’ has the code to
plot the two kind graphs. To plot the graphs, open gnuplot, navigate to the correct directory
and simply run the command,

`load ‘printGraphs.p’`



---


## Results

The following Fitness vs. Generation number plots for different values of K show the average
fitness moving towards the maximum fitness in each generation.
In more than 25 tests, the maximum fitness was reached was about ~ 5.6.

![K = 1.5e05](/K=1.5e05.png)

![K = 3.5e05](/K=3.5e05.png)

Multiple combination of values of (Ax, Ay, Az) give fitness in the range of 5.2-5.7. Some of them
are – (1.2e06, 1.2e06, 510000), (5.72e06, 5.72e06, 540000), (9.88e06, 9.88e06, 26000),
(10.04e06, 10.04e06, 26000), etc. The common pattern in all the solutions is that of,
(Ax=Ay >Az). This falls into the disk-shaped hyperfine parameter regime.

The following plots are for Singlet product yield vs. Theta. They show a steadily increasing
function for different values of K.

![PhiS K = 2e05](/PhiS_K=2e05.png)

![PhiS K = 3.5e05](/PhiS_K=3.5e05.png)


The values of the variables (Ax, Ay, Az) discovered for the maximum sensitivity help in describing the
characteristics of the nuclear part of the molecules which form radical pairs. Nature improves the
biological mechanisms generation after generation, by estimating the optimal sensitivity and hyperfine
parameters we get closer to the actual working of the avian compass. Also, research is ongoing to create
a geomagnetic sensor which can detect its location on Earth based on the local geomagnetic field using
similar mechanism. The optimized values calculated can be used for maximizing the sensitivity of the
artificial compass. Future scope of work includes the study of the effects of recombination rate and the
initial state on the sensitivity of the avian compass.



---


