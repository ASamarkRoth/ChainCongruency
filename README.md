# Chain Congruency

The congruency within and between sets of decay chains of superheavy nuclei are evaluated on the basis of statistical method presented by Ulrika Forsberg ([PhD Thesis, "Element 115"](http://portal.research.lu.se/portal/files/7495513/thesis.pdf)).

## Running the Jupyter-Notebook

You can run it in the web browser on mybinder (without installing anything) by clicking the link here (ignore the following in that case). 

1. It is possible to run the notebook on your local computer as follows:
2. Install [miniconda3](https://conda.io/miniconda.html) alternatively the full [anaconda3](https://www.anaconda.com/download) environment on your laptop (the latter is **much** larger).
3 [Download](https://github.com/mlund/jupyter-course/archive/master.zip) this repository.
4 Install and activate the `ChainCongruency` environment described by the file [`environment.yml`](/environment.yml)  by running the following in a terminal:
```bash
conda env create -f environment.yml
source activate ChainCongruency
./postBuild
```
5. Run the notebook via `jupyter-notebook ChainCongruencyMain.ipynb`

