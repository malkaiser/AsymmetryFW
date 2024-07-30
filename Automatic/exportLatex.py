import numpy as np

analyseFolder = "numbersPoPy"
table = open('./numbersTable.txt', "w")
tableRQCD = open("./rQCDTable.txt","w")
tableAsymmetry = open("./asymmetriesTable.txt","w")

def line(array1, array2):
    array = array1
    array[4] = array[4]+"("+array2[4]+")"
    array[5] = array[5]+"("+array2[5]+")"
    array[14] = array[14]+"("+array2[14]+")"
    array[15] = array[15]+"("+array2[15]+")"
    array[18] = array[18]+"("+array2[18]+")"
    array[19] = array[19]+"("+array2[19].strip()+")"
    string = ""
    for i in range(0,len(array)):
        string = string+" & "+array[i]
    return string

def rQCDformat(array):
    rQCD = float(array[0])
    uncRQCD = float(array[1])
    if np.abs(rQCD) > 1:
        leading_r = round(rQCD*100)/100
        leading_unc = round(uncRQCD*100)/100
        string = str(leading_r)+"\\pm"+str(leading_unc)
    if np.abs(rQCD) < 1:
        leading_r = round(rQCD*1000)/1000
        leading_unc = round(uncRQCD*1000)/1000
        string = str(leading_r)+"\\pm"+str(leading_unc)
    return string

def asymmformat(array):
    asymm = float(array[0])
    uncAsymm = float(array[1])
    scale_asymm = np.log10(np.abs(asymm))
    scale_unc = np.log10(np.abs(uncAsymm))
    
    if (scale_asymm < scale_unc or asymm == 0):
        scale = np.ceil(np.abs(scale_unc))
    elif (scale_asymm > scale_unc or uncAsymm == 0):
        scale = np.ceil(np.abs(scale_asymm))
    asymm = asymm*10**scale
    uncAsymm = uncAsymm*10**scale
    string = "$({0:.1f} \\pm {1:.1f})\\times10^{{{2:.0f}}}$".format(asymm,uncAsymm,-scale)
    return string

pl3p = open(analyseFolder+'/pl3p.txt').readlines()[1].split(' & ')
pl1p = open(analyseFolder+'/pl1p.txt').readlines()[1].split(' & ')
nl3p = open(analyseFolder+'/nl3p.txt').readlines()[1].split(' & ')
nl1p = open(analyseFolder+'/nl1p.txt').readlines()[1].split(' & ')

bi_pl1p = open(analyseFolder+'/bi_pl1p.txt').readlines()[1].split(' & ')
bi_pl3p = open(analyseFolder+'/bi_pl3p.txt').readlines()[1].split(' & ')
bi_nl1p = open(analyseFolder+'/bi_nl1p.txt').readlines()[1].split(' & ')
bi_nl3p = open(analyseFolder+'/bi_nl3p.txt').readlines()[1].split(' & ')

ss_pl1p = open(analyseFolder+'/ss_pl1p.txt').readlines()[1].split(' & ')
ss_pl3p = open(analyseFolder+'/ss_pl3p.txt').readlines()[1].split(' & ')
ss_nl1p = open(analyseFolder+'/ss_nl1p.txt').readlines()[1].split(' & ')
ss_nl3p = open(analyseFolder+'/ss_nl3p.txt').readlines()[1].split(' & ')

fi_pl1p = open(analyseFolder+'/fi_pl1p.txt').readlines()[1].split(' & ')
fi_pl3p = open(analyseFolder+'/fi_pl3p.txt').readlines()[1].split(' & ')
fi_nl1p = open(analyseFolder+'/fi_nl1p.txt').readlines()[1].split(' & ')
fi_nl3p = open(analyseFolder+'/fi_nl3p.txt').readlines()[1].split(' & ')

analyseFolderSherpa = "numbersSherpa"

pl3p_corr = open(analyseFolderSherpa+'/pl3p.txt').readlines()[1].split(' & ')
pl1p_corr = open(analyseFolderSherpa+'/pl1p.txt').readlines()[1].split(' & ')
nl3p_corr = open(analyseFolderSherpa+'/nl3p.txt').readlines()[1].split(' & ')
nl1p_corr = open(analyseFolderSherpa+'/nl1p.txt').readlines()[1].split(' & ')

bi_pl1p_corr = open(analyseFolderSherpa+'/bi_pl1p.txt').readlines()[1].split(' & ')
bi_pl3p_corr = open(analyseFolderSherpa+'/bi_pl3p.txt').readlines()[1].split(' & ')
bi_nl1p_corr = open(analyseFolderSherpa+'/bi_nl1p.txt').readlines()[1].split(' & ')
bi_nl3p_corr = open(analyseFolderSherpa+'/bi_nl3p.txt').readlines()[1].split(' & ')

ss_pl1p_corr = open(analyseFolderSherpa+'/ss_pl1p.txt').readlines()[1].split(' & ')
ss_pl3p_corr = open(analyseFolderSherpa+'/ss_pl3p.txt').readlines()[1].split(' & ')
ss_nl1p_corr = open(analyseFolderSherpa+'/ss_nl1p.txt').readlines()[1].split(' & ')
ss_nl3p_corr = open(analyseFolderSherpa+'/ss_nl3p.txt').readlines()[1].split(' & ')

fi_pl1p_corr = open(analyseFolderSherpa+'/fi_pl1p.txt').readlines()[1].split(' & ')
fi_pl3p_corr = open(analyseFolderSherpa+'/fi_pl3p.txt').readlines()[1].split(' & ')
fi_nl1p_corr = open(analyseFolderSherpa+'/fi_nl1p.txt').readlines()[1].split(' & ')
fi_nl3p_corr = open(analyseFolderSherpa+'/fi_nl3p.txt').readlines()[1].split(' & ')

pl3p = line(pl3p,pl3p_corr)
pl1p = line(pl1p,pl1p_corr)
nl3p = line(nl3p,nl3p_corr)
nl1p = line(nl1p,nl1p_corr)

fi_pl3p = line(fi_pl3p,fi_pl3p_corr)
fi_pl1p = line(fi_pl1p,fi_pl1p_corr)
fi_nl3p = line(fi_nl3p,fi_nl3p_corr)
fi_nl1p = line(fi_nl1p,fi_nl1p_corr)

ss_pl3p = line(ss_pl3p,ss_pl3p_corr)
ss_pl1p = line(ss_pl1p,ss_pl1p_corr)
ss_nl3p = line(ss_nl3p,ss_nl3p_corr)
ss_nl1p = line(ss_nl1p,ss_nl1p_corr)

bi_pl3p = line(bi_pl3p,bi_pl3p_corr)
bi_pl1p = line(bi_pl1p,bi_pl1p_corr)
bi_nl3p = line(bi_nl3p,bi_nl3p_corr)
bi_nl1p = line(bi_nl1p,bi_nl1p_corr)

table.write("(A) $Z\\rightarrow\\tau\\tau$ Signal Region & (+) & One "+pl1p+"\\\\"+"\n")
table.write(" & & Three "+pl3p+"\\\\"+"\n")
table.write(" & (-) & One "+nl1p+"\\\\"+"\n")
table.write(" & & Three "+nl3p+"\\\\"+"\n")

table.write("(B) Loose Iso OR LNT Tau & (+) & One "+fi_pl1p+"\\\\"+"\n")
table.write(" & & Three "+fi_pl3p+"\\\\"+"\n")
table.write(" & (-) & One "+fi_nl1p+"\\\\"+"\n")
table.write(" & & Three "+fi_nl3p+"\\\\"+"\n")

table.write("(C) SR BUT Same Sign & (+) & One "+ss_pl1p+"\\\\"+"\n")
table.write(" & & Three "+ss_pl3p+"\\\\"+"\n")
table.write(" & (-) & One "+ss_nl1p+"\\\\"+"\n")
table.write(" & & Three "+ss_nl3p+"\\\\"+"\n")

table.write("(D) SR BUT Both Inverted & (+) & One "+bi_pl1p+"\\\\"+"\n")
table.write(" & & Three "+bi_pl3p+"\\\\"+"\n")
table.write(" & (-) & One "+bi_nl1p+"\\\\"+"\n")
table.write(" & & Three "+bi_nl3p+"\\\\"+"\n")
table.close()

data_PoPy = np.genfromtxt("numbersPoPy/asymmetry.txt",delimiter=", ",dtype = str)
data_Sherpa = np.genfromtxt("numbersSherpa/asymmetry.txt", delimiter=", ",dtype = str)

dict_PoPy = {}
dict_Sherpa = {}
for i in range(0,np.shape(data_PoPy)[0]):
    dict_PoPy[data_PoPy[i,0]] = np.array([data_PoPy[i,1],data_PoPy[i,2]])
    dict_Sherpa[data_Sherpa[i,0]] = np.array([data_Sherpa[i,1],data_Sherpa[i,2]])

tableRQCD.write("(+) & One & $"+rQCDformat(dict_PoPy["RQCD 1P Plus"])+"("+rQCDformat(dict_Sherpa["RQCD 1P Plus"])+")$ & $")
tableRQCD.write(rQCDformat(dict_PoPy["RQCD Prime 1P Plus"])+"("+rQCDformat(dict_Sherpa["RQCD Prime 1P Plus"])+")$ & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 1P Plus"][0])))+"("+str(round(float(dict_Sherpa["MJBG 1P Plus"][0])))+")$"+" & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 1P Plus"][1])))+"("+str(round(float(dict_Sherpa["MJBG 1P Plus"][1])))+")$"+"\\\\ \n")

tableRQCD.write(" & Three & $"+rQCDformat(dict_PoPy["RQCD 3P Plus"])+"("+rQCDformat(dict_Sherpa["RQCD 3P Plus"])+")$ & $")
tableRQCD.write(rQCDformat(dict_PoPy["RQCD Prime 3P Plus"])+"("+rQCDformat(dict_Sherpa["RQCD Prime 3P Plus"])+")$ & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 3P Plus"][0])))+"("+str(round(float(dict_Sherpa["MJBG 3P Plus"][0])))+")$"+" & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 3P Plus"][1])))+"("+str(round(float(dict_Sherpa["MJBG 3P Plus"][1])))+")$"+"\\\\ \n")

tableRQCD.write("(-) & One & $"+rQCDformat(dict_PoPy["RQCD 1P Minus"])+"("+rQCDformat(dict_Sherpa["RQCD 1P Minus"])+")$ & $")
tableRQCD.write(rQCDformat(dict_PoPy["RQCD Prime 1P Minus"])+"("+rQCDformat(dict_Sherpa["RQCD Prime 1P Minus"])+")$ & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 1P Minus"][0])))+"("+str(round(float(dict_Sherpa["MJBG 1P Minus"][0])))+")$ "+" & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 1P Minus"][1])))+"("+str(round(float(dict_Sherpa["MJBG 1P Minus"][1])))+")$ "+"\\\\ \n")

tableRQCD.write(" & Three & $"+rQCDformat(dict_PoPy["RQCD 3P Minus"])+"("+rQCDformat(dict_Sherpa["RQCD 3P Minus"])+")$ & $")
tableRQCD.write(rQCDformat(dict_PoPy["RQCD Prime 3P Minus"])+"("+rQCDformat(dict_Sherpa["RQCD Prime 3P Minus"])+")$ & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 3P Minus"][0])))+"("+str(round(float(dict_Sherpa["MJBG 3P Minus"][0])))+")$ "+" & $")
tableRQCD.write(str(round(float(dict_PoPy["MJBG 3P Minus"][1])))+"("+str(round(float(dict_Sherpa["MJBG 3P Minus"][1])))+")$ "+"\\\\ \n")

tableAsymmetry.write("W+Jets & "+asymmformat(dict_PoPy["W+Jets 1P"])+" & - & "+asymmformat(dict_PoPy["W+Jets 3P"])+" & - & "+asymmformat(dict_PoPy["W+Jets Tot"])+" & - \\\\ \n")
tableAsymmetry.write("$Z\\rightarrow\\tau\\tau$ & "+asymmformat(dict_PoPy["Ztautau 1P"])+" & "+asymmformat(dict_Sherpa["Ztautau 1P"])+"& "+asymmformat(dict_PoPy["Ztautau 3P"])+" & "+asymmformat(dict_Sherpa["Ztautau 3P"])+" & "+asymmformat(dict_PoPy["Ztautau Tot"])+" & "+asymmformat(dict_Sherpa["Ztautau Tot"])+" \\\\ \n")
tableAsymmetry.write("$Z\\rightarrow\\mu\\mu$ & "+asymmformat(dict_PoPy["Zmumu 1P"])+" & - & "+asymmformat(dict_PoPy["Zmumu 3P"])+" & - & "+asymmformat(dict_PoPy["Zmumu Tot"])+" & - \\\\ \n")
tableAsymmetry.write("$t\\bar{{t}}$ & "+asymmformat(dict_PoPy["ttbar 1P"])+" & - & "+asymmformat(dict_PoPy["ttbar 3P"])+" & - & "+asymmformat(dict_PoPy["ttbar Tot"])+" & - \\\\ \n")
tableAsymmetry.write("Single Top & "+asymmformat(dict_PoPy["Singletop 1P"])+" & - & "+asymmformat(dict_PoPy["Singletop 3P"])+" & - & "+asymmformat(dict_PoPy["Singletop Tot"])+" & - \\\\ \n")
tableAsymmetry.write("VV & "+asymmformat(dict_PoPy["VV 1P"])+" & - & "+asymmformat(dict_PoPy["VV 3P"])+" & - & "+asymmformat(dict_PoPy["VV Tot"])+" & - \\\\ \n")
tableAsymmetry.write("VBF & "+asymmformat(dict_PoPy["VBF 1P"])+" & "+asymmformat(dict_Sherpa["VBF 1P"])+"& "+asymmformat(dict_PoPy["VBF 3P"])+" & "+asymmformat(dict_Sherpa["VBF 3P"])+" & "+asymmformat(dict_PoPy["VBF Tot"])+" & "+asymmformat(dict_Sherpa["VBF Tot"])+" \\\\ \n")
tableAsymmetry.write("Higgs & "+asymmformat(dict_PoPy["Higgs 1P"])+" & - & "+asymmformat(dict_PoPy["Higgs 3P"])+" & - & "+asymmformat(dict_PoPy["Higgs Tot"])+" & - \\\\ \n")
tableAsymmetry.write("Est. MJBG & "+asymmformat(dict_PoPy["MJBG 1P"])+" & "+asymmformat(dict_Sherpa["MJBG 1P"])+"& "+asymmformat(dict_PoPy["MJBG 3P"])+" & "+asymmformat(dict_Sherpa["MJBG 3P"])+" & "+asymmformat(dict_PoPy["MJBG Tot"])+" & "+asymmformat(dict_Sherpa["MJBG Tot"])+" \\\\ \n")
tableAsymmetry.write("\\hline \n")
tableAsymmetry.write("MC + MJBG & "+asymmformat(dict_PoPy["MC+MJBG 1P"])+" & "+asymmformat(dict_Sherpa["MC+MJBG 1P"])+"& "+asymmformat(dict_PoPy["MC+MJBG 3P"])+" & "+asymmformat(dict_Sherpa["MC+MJBG 3P"])+" & "+asymmformat(dict_PoPy["MC+MJBG Total"])+" & "+asymmformat(dict_Sherpa["MC+MJBG Total"])+" \\\\ \n")
tableAsymmetry.write("Data & "+asymmformat(dict_PoPy["Data 1P"])+" & - & "+asymmformat(dict_PoPy["Data 3P"])+" & - & "+asymmformat(dict_PoPy["Data Tot"])+" & - \\\\ \n")