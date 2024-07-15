var="../OutputChargeProng/ZtautauSameSignNegativeLep/MuonChannel/OneProng"
echo ""
echo "Outputting to ${var}"

if [ -d $var ]; then
  RED='\033[0;35m'
  NC='\033[0m' # No Color
  echo -e "${RED}####################################################"
  echo -e "${var} ALREADY EXISTS!"
  echo -e "####################################################${NC}"
fi

echo ""
echo "Are you absolutely sure you wish to proceed?"
read varInput
if [ $varInput == "yes" ]
then
    python3 RunAnalysis.py --samples All --outputDir $var --j 64 --verbosity INFO --treeName NOMINAL --jobType h
else
    echo "exiting..."
fi