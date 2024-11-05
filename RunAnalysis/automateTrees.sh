if [ $1 == "" ] || [ $2 == "" ] || [ $3 == "" ] || [ $4 == "" ] || [ $5 == "" ]; then
  echo "Incomplete input!"
  exit
else
  if [ $1 == "oppSign" ]; then
    if [ $2 == "passed" ]; then
      if [ $3 == "positive" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/SignalRegion/PositiveLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/SignalRegion/PositiveLepton/ThreeProng"
        fi
      elif [ $3 == "negative" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/SignalRegion/NegativeLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/SignalRegion/NegativeLepton/ThreeProng"
        fi
      fi
    elif [ $2 == "failedORLNT" ]; then
      if [ $3 == "positive" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/FailedORLNT/PositiveLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/FailedORLNT/PositiveLepton/ThreeProng"
        fi
      elif [ $3 == "negative" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/FailedORLNT/NegativeLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/FailedORLNT/NegativeLepton/ThreeProng"
        fi
      fi
    fi
  elif [ $1 == "sameSign" ]; then
    if [ $2 == "passed" ]; then
      if [ $3 == "positive" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/SameSign/PositiveLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/SameSign/PositiveLepton/ThreeProng"
        fi
      elif [ $3 == "negative" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/SameSign/NegativeLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/SameSign/NegativeLepton/ThreeProng"
        fi
      fi
    elif [ $2 == "failedORLNT" ]; then
      if [ $3 == "positive" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/BothInverted/PositiveLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/BothInverted/PositiveLepton/ThreeProng"
        fi
      elif [ $3 == "negative" ]; then
        if [ $4 == "one" ]; then
          var="../${5}/BothInverted/NegativeLepton/OneProng"
        elif [ $4 == "three" ]; then
          var="../${5}/BothInverted/NegativeLepton/ThreeProng"
        fi
      fi
    fi
  else
    echo "Invalid input!"
    exit
  fi
fi # First if statement
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
  python3 RunAnalysis.py --sign $1 --isoRNN $2 --charge $3 --prongness $4 --mass $5 --samples All --outputDir $var --j 256 --verbosity INFO --treeName NOMINAL --jobType n
  cp ../Automatic/konkatenate.py $var/NOMINAL/
  cd $var/NOMINAL/
  python3 konkatenate.py --j 64
  cd ..
  rm -r ./NOMINAL
fi