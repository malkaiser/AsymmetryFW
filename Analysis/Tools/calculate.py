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

pl3p = np.genfromtxt('PoPy/pl3p.txt',skip_header=1, delimiter = ' & ')
pl1p = np.genfromtxt('PoPy/pl1p.txt',skip_header=1, delimiter = ' & ')
nl3p = np.genfromtxt('PoPy/nl3p.txt',skip_header=1, delimiter = ' & ')
nl1p = np.genfromtxt('PoPy/nl1p.txt',skip_header=1, delimiter = ' & ')
'''
RQCD, uncQCD = calculateRQCD(15962,496,9907,202)
print(RQCD, uncQCD)
print(calculateMJBG(RQCD,uncQCD,1706,81))

'''
pl3p_sum = 0
pl3p_unc_square = 0
nl3p_sum = 0
nl3p_unc_square = 0

pl1p_sum = 0
pl1p_unc_square = 0
nl1p_sum = 0
nl1p_unc_square = 0

for i in range(0,9):
    positive_lepton_3p = pl3p[2*i]
    pl3p_sum += pl3p[2*i]

    positive_uncertainty_3p = pl3p[2*i+1]
    pl3p_unc_square += pl3p[2*i+1]**2

    negative_lepton_3p = nl3p[2*i]
    nl3p_sum += nl3p[2*i]

    negative_uncertainty_3p = nl3p[2*i+1]
    nl3p_unc_square += nl3p[2*i+1]**2

    positive_lepton_1p = pl1p[2*i]
    pl1p_sum += pl1p[2*i]

    positive_uncertainty_1p = pl1p[2*i+1]
    pl1p_unc_square += pl1p[2*i+1]**2

    negative_lepton_1p = nl1p[2*i]
    nl1p_sum += nl1p[2*i]
    
    negative_uncertainty_1p = nl1p[2*i+1]
    nl1p_unc_square += nl1p[2*i+1]**2

    positive_lepton = positive_lepton_1p + positive_lepton_3p
    positive_uncertainty = np.sqrt(positive_uncertainty_1p**2+positive_uncertainty_3p**2)
    negative_lepton = negative_lepton_1p + negative_lepton_3p
    negative_uncertainty = np.sqrt(negative_uncertainty_1p**2+negative_uncertainty_3p**2)
    print(str(i)+" 1P: ",str(calculateAsymmetry(positive_lepton_1p, positive_uncertainty_1p, negative_lepton_1p, negative_uncertainty_1p)))
    print(str(i)+" 3P: ",str(calculateAsymmetry(positive_lepton_3p, positive_uncertainty_3p, negative_lepton_3p, negative_uncertainty_3p)))
    print(str(i)+" Tot: ",str(calculateAsymmetry(positive_lepton, positive_uncertainty, negative_lepton, negative_uncertainty)),"\n")

rQCD_pl1p, unc_rQCD_pl1p = calculateRQCD(39652, 956, 33023, 416) 
rQCD_pl3p, unc_rQCD_pl3p = calculateRQCD(16905, 506, 11265, 232) 
rQCD_nl1p, unc_rQCD_nl1p = calculateRQCD(37967, 920, 28577, 359)
rQCD_nl3p, unc_rQCD_nl3p = calculateRQCD(15962, 496, 9907, 202) 

positive_lepton_1p_MJBG , positive_uncertainty_1p_MJBG = calculateMJBG(rQCD_pl1p, unc_rQCD_pl1p, 8381, 204) 
positive_lepton_3p_MJBG , positive_uncertainty_3p_MJBG = calculateMJBG(rQCD_pl3p, unc_rQCD_pl3p, 1787, 97) 
negative_lepton_1p_MJBG , negative_uncertainty_1p_MJBG = calculateMJBG(rQCD_nl1p, unc_rQCD_nl1p, 6729, 187)
negative_lepton_3p_MJBG , negative_uncertainty_3p_MJBG = calculateMJBG(rQCD_nl3p, unc_rQCD_nl3p, 1706, 81) 

pl3p_sum += positive_lepton_3p_MJBG
pl3p_unc_square += positive_uncertainty_3p_MJBG**2
nl3p_sum += negative_lepton_3p_MJBG
nl3p_unc_square += negative_uncertainty_3p_MJBG**2

pl1p_sum += positive_lepton_1p_MJBG
pl1p_unc_square += positive_uncertainty_1p_MJBG**2
nl1p_sum += negative_lepton_1p_MJBG
nl1p_unc_square += negative_uncertainty_1p_MJBG**2

pl_sum = pl3p_sum + pl1p_sum
nl_sum = nl3p_sum + nl1p_sum
pl_square_unc = pl3p_unc_square + pl1p_unc_square
nl_square_unc = nl3p_unc_square + nl1p_unc_square

positive_lepton_MJBG = positive_lepton_1p_MJBG + positive_lepton_3p_MJBG
positive_uncertainty_MJBG = np.sqrt(positive_uncertainty_1p_MJBG**2+positive_uncertainty_3p_MJBG**2)
negative_lepton_MJBG = negative_lepton_1p_MJBG + negative_lepton_3p_MJBG
negative_uncertainty_MJBG = np.sqrt(negative_uncertainty_1p_MJBG**2+negative_uncertainty_3p_MJBG**2)

print(positive_lepton_3p_MJBG)
print(positive_lepton_1p_MJBG)

print("MJBG 1P: ",str(calculateAsymmetry(positive_lepton_1p_MJBG, positive_uncertainty_1p_MJBG, negative_lepton_1p_MJBG, negative_uncertainty_1p_MJBG)))
print("MJBG 3P: ",str(calculateAsymmetry(positive_lepton_3p_MJBG, positive_uncertainty_3p_MJBG, negative_lepton_3p_MJBG, negative_uncertainty_3p_MJBG)))
print("MJBG Tot: ",str(calculateAsymmetry(positive_lepton_MJBG, positive_uncertainty_MJBG, negative_lepton_MJBG, negative_uncertainty_MJBG)))

print("MC+MJBG 1P: ",calculateAsymmetry(pl1p_sum, np.sqrt(pl1p_unc_square), nl1p_sum, np.sqrt(nl1p_unc_square)))
print("MC+MJBG 3P: ",calculateAsymmetry(pl3p_sum, np.sqrt(pl3p_unc_square), nl3p_sum, np.sqrt(nl3p_unc_square)))
print("MC+MJBG Total: ",calculateAsymmetry(pl_sum, np.sqrt(pl_square_unc), nl_sum, np.sqrt(nl_square_unc)))
