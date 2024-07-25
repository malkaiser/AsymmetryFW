if [ $1 == "oppSign" ]; then
  if [ $2 == "passed" ]; then
    var="../HiggsMassM3/SignalRegion/$3/$4"
  else
    var="../HiggsMassM3/FailedIsoORLNT/$3/$4"
  fi
else
  if [ $2 == "passed" ]; then
    var="../HiggsMassM3/SameSign/$3/$4"
  else
    var="../HiggsMassM3/BothInverted/$3/$4"
  fi
fi

echo ""
echo "Outputting to ${var}"

if [ -d $var ]; then
  RED='\033[0;35m'
  NC='\033[0m' # No Color
  echo -e "${RED}####################################################"
  echo -e "${var} ALREADY EXISTS!"
  echo -e "####################################################${NC}"]
  echo "exiting..."
else
  python3 RunAnalysis.py --sign $1 --isoRNN $2 --charge $3 --prongness $4 --samples All --outputDir $var --j 64 --verbosity INFO --treeName NOMINAL --jobType h
fi

cp ../Analysis/Tools/concatenate.sh $var/NOMINAL/
cd $var/NOMINAL/
bash concatenate.sh