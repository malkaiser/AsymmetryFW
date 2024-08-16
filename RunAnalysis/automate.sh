if [ $1 == "oppSign" ]; then
  if [ $2 == "passed" ]; then
    if [ $3 == "positive" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/SignalRegion/PositiveLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/SignalRegion/PositiveLepton/ThreeProng"
      fi
    elif [ $3 == "negative" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/SignalRegion/NegativeLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/SignalRegion/NegativeLepton/ThreeProng"
      fi
    fi
  else # $2 == negative
    if [ $3 == "positive" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/FailedIsoORLNT/PositiveLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/FailedIsoORLNT/PositiveLepton/ThreeProng"
      fi
    elif [ $3 == "negative" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/FailedIsoORLNT/NegativeLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/FailedIsoORLNT/NegativeLepton/ThreeProng"
      fi
    fi
  fi
else
  if [ $2 == "passed" ]; then
    if [ $3 == "positive" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/SameSign/PositiveLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/SameSign/PositiveLepton/ThreeProng"
      fi
    elif [ $3 == "negative" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/SameSign/NegativeLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/SameSign/NegativeLepton/ThreeProng"
      fi
    fi
  else
    if [ $3 == "positive" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/BothInverted/PositiveLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/BothInverted/PositiveLepton/ThreeProng"
      fi
    elif [ $3 == "negative" ]; then
      if [ $4 == "one" ]; then
        var="../HighMassBDT/BothInverted/NegativeLepton/OneProng"
      elif [ $4 == "three" ]; then
        var="../HighMassBDT/BothInverted/NegativeLepton/ThreeProng"
      fi
    fi
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
  python3 RunAnalysis.py --sign $1 --isoRNN $2 --charge $3 --prongness $4 --samples All --outputDir $var --j 192 --verbosity INFO --treeName NOMINAL --jobType h
  cp ../Automatic/concatenate.sh $var/NOMINAL/
  cd $var/NOMINAL/
  bash concatenate.sh
  cd ..
  rm -r ./NOMINAL
fi