python3 RunAnalysis.py  --sign $1 --isoRNN $2 --charge $3 --prongness $4 --samples All --outputDir ../Trees/$1/$2/$3/$4 --j 128 --verbosity INFO --treeName NOMINAL --jobType n
cd ../Trees/$1/$2/$3/$4
hadd train.root ./NOMINAL/*.root
rm -r ./NOMINAL