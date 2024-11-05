var="../Test"
echo ""
echo "Outputting to ${var}"

if [ -d $var ]; then
  RED='\033[0;35m'
  NC='\033[0m' # No Color
  echo -e "${RED}####################################################"
  echo -e "${var} ALREADY EXISTS!"
  echo -e "####################################################${NC}"
fi

echo "Are you absolutely sure you wish to proceed?"
read varInput
if [ $varInput == "yes" ]
then
    python3 RunAnalysis.py --sign oppSign --charge positive --isoRNN passed --prongness three --samples All --outputDir $var --j 64 --verbosity DEBUG --treeName NOMINAL --jobType hnr

else
    echo "Invalid input \"$varInput\"!"
    echo "exiting..."
fi