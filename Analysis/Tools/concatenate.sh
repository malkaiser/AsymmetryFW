mkdir -p ../Analysis/

hadd gg_Higgs.root ggH*.root
mv gg_Higgs.root ../Analysis/

hadd singletop.root st_schan_atop*.root st_schan_top*.root st_tchan_atop*.root st_tchan_top*.root st_wt_atop*.root st_wt_top*.root
mv singletop.root ../Analysis/

hadd ttbar.root ttbar*.root
mv ttbar.root ../Analysis/

hadd VBF_PoPy.root VBF_Zee_201*.root VBF_Zmumu_201*.root VBF_Ztautau_201*.root VBFH*.root
mv VBF_PoPy.root ../Analysis/

hadd VBF_sherpa.root VBF_Zee_sherpa*.root VBF_Zmumu_sherpa*.root VBF_Ztautau_sherpa*.root
mv VBF_sherpa.root ../Analysis/

hadd VV_EWK_SemiLep.root VV_EWK_SemiLep*.root
mv VV_EWK_SemiLep.root ../Analysis/

hadd VV_EWK.root VV_EWK1*.root  VV_EWK2*.root  VV_EWK3*.root  VV_EWK4*.root VV_EWK5*.root VV_EWK6*.root VV_EWK7*.root VV_EWK8*.root 
mv VV_EWK.root ../Analysis/

hadd W_EWK_PoPy.root W_EWK_PoPy*.root
mv W_EWK_PoPy.root ../Analysis/

hadd W_EWK_sherpa.root W_EWK_sherpa*.root
mv W_EWK_sherpa.root ../Analysis/

hadd WmH.root WmH*.root
mv WmH.root ../Analysis/

hadd Wjets.root Wminusenu*.root Wminusmunu*.root Wminustaunu*.root Wplusenu*.root Wplusmunu*.root Wplustaunu*.root
mv Wjets.root ../Analysis/

hadd Zee_PoPy.root Zee*.root
mv Zee_PoPy.root ../Analysis/

hadd ZHllbb.root ZHllbb*.root
mv ZHllbb.root ../Analysis/

hadd ZHlltautau.root ZHlltautau*.root
mv ZHlltautau.root ../Analysis/

hadd Zmumu_PoPy.root Zmumu_201*.root
mv Zmumu_PoPy.root ../Analysis/

hadd Ztautau_PoPy.root Ztautau_201*.root
mv Ztautau_PoPy.root ../Analysis/

hadd Ztautau_MG.root Ztautau_MG1*.root Ztautau_MG2*.root Ztautau_MG3*.root Ztautau_MG4*.root Ztautau_MG5*.root
mv Ztautau_MG.root ../Analysis/

hadd Ztautau_MGNLO.root Ztautau_MGNLO*.root
mv Ztautau_MGNLO.root ../Analysis/

hadd Ztautau_sherpa.root Ztautau_sherpa*.root
mv Ztautau_sherpa.root ../Analysis/

hadd Ztautau_SherpaNLO.root Ztautau_SherpaNLO*.root
mv Ztautau_SherpaNLO.root ../Analysis/

hadd VV.root llll_*.root lllv_*.root llvv_*.root lvvv_*.root ZqqZvv_*.root ZqqZll_*.root WqqZvv_*.root WqqZll_*.root WlvZqq_*.root
mv VV.root ../Analysis

hadd data.root data*.root
mv data.root ../Analysis