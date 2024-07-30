mkdir Root/
hadd data.root ../OneProng/Root/data.root ../ThreeProng/Root/data.root
mv data.root Root/

hadd gg_Higgs.root ../OneProng/Root/gg_Higgs.root ../ThreeProng/Root/gg_Higgs.root
mv gg_Higgs.root Root/

hadd MJBG_prime_Sherpa.root ../OneProng/Root/MJBG_prime_Sherpa.root ../ThreeProng/Root/MJBG_prime_Sherpa.root
mv MJBG_prime_Sherpa.root Root/

hadd MJBG_Sherpa.root ../OneProng/Root/MJBG_Sherpa.root ../ThreeProng/Root/MJBG_Sherpa.root
mv MJBG_Sherpa.root Root/

hadd MJBG_prime_PoPy.root ../OneProng/Root/MJBG_prime_PoPy.root ../ThreeProng/Root/MJBG_prime_PoPy.root
mv MJBG_prime_PoPy.root Root/

hadd MJBG_PoPy.root ../OneProng/Root/MJBG_PoPy.root ../ThreeProng/Root/MJBG_PoPy.root
mv MJBG_PoPy.root Root/

hadd singletop.root ../OneProng/Root/singletop.root ../ThreeProng/Root/singletop.root
mv singletop.root Root/

hadd ttbar.root ../OneProng/Root/ttbar.root ../ThreeProng/Root/ttbar.root
mv ttbar.root Root/

hadd VBF_PoPy.root ../OneProng/Root/VBF_PoPy.root ../ThreeProng/Root/VBF_PoPy.root
mv VBF_PoPy.root Root/

hadd VBF_sherpa.root ../OneProng/Root/VBF_sherpa.root ../ThreeProng/Root/VBF_sherpa.root
mv VBF_sherpa.root Root/

hadd VV.root ../OneProng/Root/VV.root ../ThreeProng/Root/VV.root
mv VV.root Root/

hadd Wjets.root ../OneProng/Root/Wjets.root ../ThreeProng/Root/Wjets.root
mv Wjets.root Root/

hadd Zee_PoPy.root ../OneProng/Root/Zee_PoPy.root ../ThreeProng/Root/Zee_PoPy.root
mv Zee_PoPy.root Root/

hadd Zmumu_PoPy.root ../OneProng/Root/Zmumu_PoPy.root ../ThreeProng/Root/Zmumu_PoPy.root
mv Zmumu_PoPy.root Root/

hadd Ztautau_MG.root ../OneProng/Root/Ztautau_MG.root ../ThreeProng/Root/Ztautau_MG.root
mv Ztautau_MG.root Root/

hadd Ztautau_MGNLO.root ../OneProng/Root/Ztautau_MGNLO.root ../ThreeProng/Root/Ztautau_MGNLO.root
mv Ztautau_MGNLO.root Root/

hadd Ztautau_PoPy.root ../OneProng/Root/Ztautau_PoPy.root ../ThreeProng/Root/Ztautau_PoPy.root
mv Ztautau_PoPy.root Root/

hadd Ztautau_sherpa.root ../OneProng/Root/Ztautau_sherpa.root ../ThreeProng/Root/Ztautau_sherpa.root
mv Ztautau_sherpa.root Root/

hadd Ztautau_SherpaNLO.root ../OneProng/Root/Ztautau_SherpaNLO.root ../ThreeProng/Root/Ztautau_SherpaNLO.root
mv Ztautau_SherpaNLO.root Root/

rm -r ./PoPy ./Sherpa

mkdir ./PoPy/
echo -e "PoPy\nNone" | python3 Example.py
mv ./plots ./PoPy/plotsBefore

echo -e "PoPy\nPrime" | python3 Example.py
mv ./plots ./PoPy/plotsPrime

echo -e "PoPy\nUnprimed" | python3 Example.py
mv ./PoPy/plots ./PoPy/plotsRQCD

mkdir ./Sherpa/
echo -e "Sherpa\nNone" | python3 Example.py
mv ./plots ./Sherpa/plotsBefore

echo -e "Sherpa\nPrime" | python3 Example.py
mv ./plots ./Sherpa/plotsPrime

echo -e "PoPy\nUnprimed" | python3 Example.py
mv ./Sherpa/plots ./Sherpa/plotsRQCD