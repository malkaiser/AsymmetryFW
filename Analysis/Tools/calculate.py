import numpy as np

def calculateAsymmetry(positive, positive_unc, negative, negative_unc):
    asymmetry = (negative-positive)/(negative+positive)
    unc_squared = (negative_unc**2)*((2*positive)/(negative+positive)**2)**2
    unc_squared += (positive_unc**2)*((2*negative)/(negative+positive)**2)**2
    return asymmetry, np.sqrt(unc_squared)

def calculateRQCD(control_region, cr_unc, both_inverted, bi_unc):
    rQCD = control_region/both_inverted
    unc_rQCD = rQCD*np.sqrt((cr_unc/control_region)**2 + (bi_unc/both_inverted)**2)
    return rQCD, unc_rQCD

def calculateMJBG(rQCD,unc_rQCD, control_region, cr_unc):
    n_MJBG = control_region*rQCD
    unc_MJBG = n_MJBG*np.sqrt((unc_rQCD/rQCD)**2+(cr_unc/control_region)**2)
    return n_MJBG, unc_MJBG

positive_lepton_1p = 804
positive_uncertainty_1p =  8
negative_lepton_1p = 761
negative_uncertainty_1p =  8 

positive_lepton_3p = 172
positive_uncertainty_3p =   3  
negative_lepton_3p = 160
negative_uncertainty_3p = 3.3 

positive_lepton = positive_lepton_1p + positive_lepton_3p
positive_uncertainty = np.sqrt(positive_uncertainty_1p**2+positive_uncertainty_3p**2)
negative_lepton = negative_lepton_1p + negative_lepton_3p
negative_uncertainty = np.sqrt(negative_uncertainty_1p**2+negative_uncertainty_3p**2)
print("1P: ",str(calculateAsymmetry(positive_lepton_1p, positive_uncertainty_1p, negative_lepton_1p, negative_uncertainty_1p)))
print("3P: ",str(calculateAsymmetry(positive_lepton_3p, positive_uncertainty_3p, negative_lepton_3p, negative_uncertainty_3p)))
print("Tot: ",str(calculateAsymmetry(positive_lepton, positive_uncertainty, negative_lepton, negative_uncertainty)))
