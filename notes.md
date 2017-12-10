# Notes on the statistical method


## Purpose

A set of decay chains;
* Are they similar to chains previously measured of a specific isotope?
* Do the chains have a common origin?
A decay chain: 
* Does it fit with the characteristics of a reference data set? 

_What has been done_: Generalisation of an existing method, which probed the likelihood that a set of lifetimes have a common origin, to instead validate sets of decay chains (i.e. groups of lifetime).

## Schmidt test
See article. 

The logarithm of the lifetimes $\theta = \ln t$) is considered instead. 
In this case the shape of the probability density distribution is independent of the decay constant $\lambda$. 
The standard deviation (the square root of the second moment) of the curve has a value of about $\sigma_{\theta} = 1.28$.
Note that this value is independent of the expected half-life of the radioactive species. 
Furthermore, in this case all lifetimes are assumed to originate from only **one** specific state.

Through Monte-Carlo simulations the distribution of this standard deviation could be obtained as a function of the number of events measured. 
Hence, also upper and lower confidence limits are available.
Analytically for infinite events: $\sigma_{\theta} = 1.28 \pm 2.15\cdot \sqrt{n}$ where $n$ is the number of events.

Applying the method: 
1. Calculate the $\sigma_{\theta}$ on the basis of the experimentally measured lifetimes. 
2. See where the obtained value lies in the distribution of $\sigma_{\theta}$.

## Generalised Schmidt test
The method is introduced and presented in [D. Rudolph et al., EPJ Web of Conferences](https://www.epj-conferences.org/articles/epjconf/pdf/2016/12/epjconf_nn2016_01001.pdf).
The article presents the generalised method applied to the short E115 decay chains.
It should correspond to scenario "8" in Ulrika's framework. 

Table 4 in [U. Forsberg et al., Physics Letters B](http://www.sciencedirect.com/science/article/pii/S0375947416300768?via%3Dihub) presents interesting values. 

Ulrika Forsberg generalised the Schmidt test by instead taking the geometric mean of the lifetimes within a decay chain and after this performed an average. 
In order to assess a final value confidence limits are simulated on the basis of the characteristics of the measured decay chains.
Missing members of decay chains are properly taken into account by the introduction of the n:th root.

Criticising paper: V B Zlokazov and V K Utyonkov 2017 J. Phys. G: Nucl. Part. Phys. 44 075107

## FoM constructed by Ulrika Forsberg
An FoM is created from first principle. 
Following this its uncertainty is thoroughly evaluated.
It seems a little to comprehensive and advanced for a small project.

## Ulrica's framework

### Random Chain Generator
The user can provide three inputs to the program located in `random_chain_generator.cxx`: 
1. Simulation method. $tau_likelihood$ is sampling from exponential distribution with $\lambda$ sampled from lower and upper limit of $\tau$ which is derived from a set average of 8.
2. Number of sets to simulate. I.e. how much data. 
3. Number of chains in each set. This number is governed by the experimental data that is to be studied.

### Probability
The user chooses the scenario he/she want to study. This means the what set of decay chains and whether simulated or experimental calculations are to be made.

**If experimental**:
* The generalised Schmidt values are simply calculated on the basis of the experimental data. 

**Else if simulated:**
* All simulated sets of decay chains (for the experimental data of interest) are considered. 
* For each set a generalised Schmidt value is calculated and stored.
* Upper and lower limits on the Schmidt value and its average are calculated on the obtained probability distribution of the same from the simulated data.
