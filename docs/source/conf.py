import subprocess, os

# Configuration file for the Sphinx documentation builder.
#
# For the full list of built-in configuration values, see the documentation:
# https://www.sphinx-doc.org/en/master/usage/configuration.html

# -- Project information -----------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#project-information

project = 'WHAD C/C++ Library'
copyright = '2024, Damien Cauquil, Romain Cayre'
author = 'Damien Cauquil, Romain Cayre'
release = '1.0.0'

# -- General configuration ---------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#general-configuration

extensions = ["breathe", "sphinx_rtd_theme", "sphinx_design"]

templates_path = ['_templates']
exclude_patterns = []



# -- Options for HTML output -------------------------------------------------
# https://www.sphinx-doc.org/en/master/usage/configuration.html#options-for-html-output

html_theme = "sphinx_rtd_theme"
html_static_path = ['_static']

# -- Options for breathe
breathe_projects = {"WHAD": "../doxygen_doc/xml/"}
breathe_default_project = "WHAD"

# Run Doxygen to generate/refresh XML files if built on RTD
read_the_docs_build = os.environ.get('READTHEDOCS', None) == 'True'
if read_the_docs_build:
     subprocess.call('cd ../; doxygen', shell=True)