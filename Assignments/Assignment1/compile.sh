#!/bin/bash

pdflatex Karthikeya_CS22B026.tex
biber Karthikeya_CS22B026
pdflatex Karthikeya_CS22B026.tex
pdflatex Karthikeya_CS22B026.tex

rm *.aux *.bbl *.blg *.log *.out *.run.xml *.bcf