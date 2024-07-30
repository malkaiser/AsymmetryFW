import os
import numpy as np

regions = ["BothInverted", "FailedORLNT", "SameSign", "SignalRegion"]
signs = ["PositiveLepton", "NegativeLepton"]
prongness = ["OneProng", "ThreeProng"]


dictionary = {"BothInverted/PositiveLepton/ThreeProng": "bi_pl3p.txt",
              "BothInverted/PositiveLepton/OneProng": "bi_pl1p.txt",
              "BothInverted/NegativeLepton/ThreeProng": "bi_nl3p.txt",
              "BothInverted/NegativeLepton/OneProng": "bi_nl1p.txt",
              
              "FailedORLNT/PositiveLepton/ThreeProng": "fi_pl3p.txt",
              "FailedORLNT/PositiveLepton/OneProng": "fi_pl1p.txt",
              "FailedORLNT/NegativeLepton/ThreeProng": "fi_nl3p.txt",
              "FailedORLNT/NegativeLepton/OneProng": "fi_nl1p.txt",

              "SameSign/PositiveLepton/ThreeProng": "ss_pl3p.txt",
              "SameSign/PositiveLepton/OneProng": "ss_pl1p.txt",
              "SameSign/NegativeLepton/ThreeProng": "ss_nl3p.txt",
              "SameSign/NegativeLepton/OneProng": "ss_nl1p.txt",

              "SignalRegion/PositiveLepton/ThreeProng": "pl3p.txt",
              "SignalRegion/PositiveLepton/OneProng": "pl1p.txt",
              "SignalRegion/NegativeLepton/ThreeProng": "nl3p.txt",
              "SignalRegion/NegativeLepton/OneProng": "nl1p.txt",
              }

rQCD_dict = {"FailedORLNT" : "RQCD",
             "SameSign" : "RQCD Prime",
             "PositiveLepton" : " PL",
             "NegativeLepton" : " NL",
             "ThreeProng" : " 3P",
             "OneProng" : " 1P",
             }

os.system("rm -r numbersPoPy/ numbersSherpa/")
os.system("mkdir numbersPoPy/")
os.system("mkdir numbersSherpa/")

for region in regions:
    for sign in signs:
        for prong in prongness:
            directory = region+"/"+sign+"/"+prong
            plotsPoPyDirectory = directory+"/plotsPoPy"
            plotsSherpaDirectory = directory+"/plotsSherpa"
            numbersPoPyDirectory = directory+"/numbersPoPy"
            numbersSherpaDirectory = directory+"/numbersSherpa"
            os.system("rm -r "+plotsPoPyDirectory+" "+plotsSherpaDirectory+" "+numbersPoPyDirectory+" "+numbersSherpaDirectory)
            if (region == "FailedORLNT" or region == "SameSign"):
                os.system("echo \""+directory+"\\n PoPy\\n no\" | python3 Example.py")
                os.system("mv "+directory+"/plots "+plotsPoPyDirectory)
                os.system("mv "+directory+"/numbers "+numbersPoPyDirectory)

                os.system("echo \""+directory+"\\n Sherpa\\n no\" | python3 Example.py")
                os.system("mv "+directory+"/plots "+plotsSherpaDirectory)
                os.system("mv "+directory+"/numbers "+numbersSherpaDirectory)
                os.system("cp "+numbersPoPyDirectory+"/lep_pt_basic_all_latex.txt "+"numbersPoPy/"+dictionary[directory])
                os.system("cp "+numbersSherpaDirectory+"/lep_pt_basic_all_latex.txt "+"numbersSherpa/"+dictionary[directory])
            else:
                os.system("echo \""+directory+"\\n PoPy\" | python3 Example.py")
                os.system("mv "+directory+"/plots "+plotsPoPyDirectory)
                os.system("mv "+directory+"/numbers "+numbersPoPyDirectory)
                
                os.system("echo \""+directory+"\\n Sherpa\" | python3 Example.py")
                os.system("mv "+directory+"/plots "+plotsSherpaDirectory)
                os.system("mv "+directory+"/numbers "+numbersSherpaDirectory)
                os.system("cp "+numbersPoPyDirectory+"/lep_pt_basic_all_latex.txt "+"numbersPoPy/"+dictionary[directory])
                os.system("cp "+numbersSherpaDirectory+"/lep_pt_basic_all_latex.txt "+"numbersSherpa/"+dictionary[directory])

os.system("echo \"numbersPoPy\" | python3 calculate.py")
os.system("echo \"numbersSherpa\" | python3 calculate.py")
rQCD_PoPy = {}
rQCD_Sherpa = {}
raw_PoPy = np.genfromtxt("numbersPoPy/rQCD.txt", delimiter = ',', dtype = str)
raw_sherpa = np.genfromtxt("numbersSherpa/rQCD.txt", delimiter =',', dtype = str)

for i in range(0,np.shape(raw_PoPy)[0]):
    rQCD_PoPy[raw_PoPy[i,0]] = np.array([raw_PoPy[i,1], raw_PoPy[i,2]])

for i in range(0,np.shape(raw_PoPy)[0]):
    rQCD_Sherpa[raw_sherpa[i,0]] = np.array([raw_sherpa[i,1], raw_sherpa[i,2]])

for region in regions:
    for sign in signs:
        for prong in prongness:
            directory = region+"/"+sign+"/"+prong
            signal_directory = "SignalRegion"+"/"+sign+"/"+prong
            plotsPoPyDirectory = directory+"/plotsPoPy"
            plotsSherpaDirectory = directory+"/plotsSherpa"
            numbersPoPyDirectory = directory+"/numbersPoPy"
            numbersSherpaDirectory = directory+"/numbersSherpa"
            if (region == "FailedORLNT"):
                name = rQCD_dict[region]+rQCD_dict[sign]+rQCD_dict[prong]
                os.system("echo \""+directory+"\\n PoPy\\n yes\\n "+rQCD_PoPy[name][0]+"\\n"+rQCD_PoPy[name][1]+"\"| python3 Example.py")
                os.system("echo \""+directory+"\\n Sherpa\\n yes \\n "+rQCD_Sherpa[name][0]+"\\n"+rQCD_Sherpa[name][1]+"\"| python3 Example.py")
                os.system("cp "+directory+"/MJBG_PoPy.root"+" "+signal_directory+"/Root/MJBG_PoPy.root")
                os.system("cp "+directory+"/MJBG_Sherpa.root"+" "+signal_directory+"/Root/MJBG_Sherpa.root")
            if (region == "SameSign"):
                name = rQCD_dict[region]+rQCD_dict[sign]+rQCD_dict[prong]
                os.system("echo \""+directory+"\\n PoPy\\n yes \\n "+rQCD_PoPy[name][0]+"\\n"+rQCD_PoPy[name][1]+"\"| python3 Example.py")
                os.system("echo \""+directory+"\\n Sherpa\\n yes \\n "+rQCD_Sherpa[name][0]+"\\n"+rQCD_Sherpa[name][1]+"\"| python3 Example.py")
                os.system("mv "+directory+"/MJBG_PoPy.root"+" "+directory+"/MJBG_prime_PoPy.root")
                os.system("mv "+directory+"/MJBG_Sherpa.root"+" "+directory+"/MJBG_prime_Sherpa.root")
                os.system("cp "+directory+"/MJBG_prime_PoPy.root"+" "+signal_directory+"/Root/MJBG_prime_PoPy.root")
                os.system("cp "+directory+"/MJBG_prime_Sherpa.root"+" "+signal_directory+"/Root/MJBG_prime_Sherpa.root")
