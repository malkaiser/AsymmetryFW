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

analyseFolder=input('Input folder?\n')

filename = analyseFolder+"/asymmetry.txt"
file = open(filename,"w")


header = np.genfromtxt(analyseFolder+'/pl3p.txt', delimiter = ' & ',dtype=str)[0,:]

pl3p = np.genfromtxt(analyseFolder+'/pl3p.txt',skip_header=1, delimiter = ' & ')
pl1p = np.genfromtxt(analyseFolder+'/pl1p.txt',skip_header=1, delimiter = ' & ')
nl3p = np.genfromtxt(analyseFolder+'/nl3p.txt',skip_header=1, delimiter = ' & ')
nl1p = np.genfromtxt(analyseFolder+'/nl1p.txt',skip_header=1, delimiter = ' & ')

bi_pl1p = np.genfromtxt(analyseFolder+'/bi_pl1p.txt',skip_header=1, delimiter = ' & ')
bi_pl3p = np.genfromtxt(analyseFolder+'/bi_pl3p.txt',skip_header=1, delimiter = ' & ')
bi_nl1p = np.genfromtxt(analyseFolder+'/bi_nl1p.txt',skip_header=1, delimiter = ' & ')
bi_nl3p = np.genfromtxt(analyseFolder+'/bi_nl3p.txt',skip_header=1, delimiter = ' & ')

ss_pl1p = np.genfromtxt(analyseFolder+'/ss_pl1p.txt',skip_header=1, delimiter = ' & ')
ss_pl3p = np.genfromtxt(analyseFolder+'/ss_pl3p.txt',skip_header=1, delimiter = ' & ')
ss_nl1p = np.genfromtxt(analyseFolder+'/ss_nl1p.txt',skip_header=1, delimiter = ' & ')
ss_nl3p = np.genfromtxt(analyseFolder+'/ss_nl3p.txt',skip_header=1, delimiter = ' & ')

fi_pl1p = np.genfromtxt(analyseFolder+'/fi_pl1p.txt',skip_header=1, delimiter = ' & ')
fi_pl3p = np.genfromtxt(analyseFolder+'/fi_pl3p.txt',skip_header=1, delimiter = ' & ')
fi_nl1p = np.genfromtxt(analyseFolder+'/fi_nl1p.txt',skip_header=1, delimiter = ' & ')
fi_nl3p = np.genfromtxt(analyseFolder+'/fi_nl3p.txt',skip_header=1, delimiter = ' & ')

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
    file.write(str(header[2*i])+" 1P: "+str(calculateAsymmetry(positive_lepton_1p, positive_uncertainty_1p, negative_lepton_1p, negative_uncertainty_1p))+"\n")
    file.write(str(header[2*i])+" 3P: "+str(calculateAsymmetry(positive_lepton_3p, positive_uncertainty_3p, negative_lepton_3p, negative_uncertainty_3p))+"\n")
    file.write(str(header[2*i])+" Tot: "+str(calculateAsymmetry(positive_lepton, positive_uncertainty, negative_lepton, negative_uncertainty))+"\n")

# RQCD section
rQCDfile = analyseFolder+'/rQCD.txt'
rQCD_pl1p, unc_rQCD_pl1p = calculateRQCD(ss_pl1p[18], ss_pl1p[19], bi_pl1p[18], bi_pl1p[19]) 
rQCD_pl3p, unc_rQCD_pl3p = calculateRQCD(ss_pl3p[18], ss_pl3p[19], bi_pl3p[18], bi_pl3p[19]) 
rQCD_nl1p, unc_rQCD_nl1p = calculateRQCD(ss_nl1p[18], ss_nl1p[19], bi_nl1p[18], bi_nl1p[19])
rQCD_nl3p, unc_rQCD_nl3p = calculateRQCD(ss_nl3p[18], ss_nl3p[19], bi_nl3p[18], bi_nl3p[19])

rQCD_prime_pl1p, unc_prime_rQCD_pl1p = calculateRQCD(fi_pl1p[18], fi_pl1p[19], bi_pl1p[18], bi_pl1p[19]) 
rQCD_prime_pl3p, unc_prime_rQCD_pl3p = calculateRQCD(fi_pl3p[18], fi_pl3p[19], bi_pl3p[18], bi_pl3p[19]) 
rQCD_prime_nl1p, unc_prime_rQCD_nl1p = calculateRQCD(fi_nl1p[18], fi_nl1p[19], bi_nl1p[18], bi_nl1p[19])
rQCD_prime_nl3p, unc_prime_rQCD_nl3p = calculateRQCD(fi_nl3p[18], fi_nl3p[19], bi_nl3p[18], bi_nl3p[19])

rQCDarray = np.array(["RQCD PL 1P",rQCD_pl1p, unc_rQCD_pl1p])
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD PL 3P",rQCD_pl3p, unc_rQCD_pl3p])))
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD NL 1P",rQCD_nl1p, unc_rQCD_nl1p])))
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD NL 3P",rQCD_nl3p, unc_rQCD_nl3p])))

rQCDarray = np.vstack((rQCDarray,np.array(["RQCD Prime PL 1P",rQCD_prime_pl1p, unc_prime_rQCD_pl1p])))
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD Prime PL 3P",rQCD_prime_pl3p, unc_prime_rQCD_pl3p])))
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD Prime NL 1P",rQCD_prime_nl1p, unc_prime_rQCD_nl1p])))
rQCDarray = np.vstack((rQCDarray,np.array(["RQCD Prime NL 3P",rQCD_prime_nl3p, unc_prime_rQCD_nl3p])))

np.savetxt(rQCDfile, rQCDarray, fmt = '%s', delimiter =',')

file.write("RQCD 1P Plus: "+ str(rQCD_pl1p)+", "+str(unc_rQCD_pl1p)+"\n")
file.write("RQCD Prime 1P Plus: "+ str(rQCD_prime_pl1p)+", "+str(unc_prime_rQCD_pl1p)+"\n")

file.write("RQCD 3P Plus: "+ str(rQCD_pl3p)+", "+str(unc_rQCD_pl3p)+"\n")
file.write("RQCD Prime 3P Plus: "+ str(rQCD_prime_pl3p)+", "+str(unc_prime_rQCD_pl3p)+"\n")

file.write("RQCD 1P Minus: "+ str(rQCD_nl1p)+", "+str(unc_rQCD_nl1p)+"\n")
file.write("RQCD Prime 1P Minus: "+ str(rQCD_prime_nl1p)+", "+str(unc_prime_rQCD_nl1p)+"\n")

file.write("RQCD 3P Minus: "+ str(rQCD_nl3p)+", "+str(unc_rQCD_nl3p)+"\n")
file.write("RQCD Prime 3P Minus: "+ str(rQCD_prime_nl3p)+", "+str(unc_prime_rQCD_nl3p)+"\n")

positive_lepton_1p_MJBG , positive_uncertainty_1p_MJBG = calculateMJBG(rQCD_pl1p, unc_rQCD_pl1p, fi_pl1p[18], fi_pl1p[19]) 
positive_lepton_3p_MJBG , positive_uncertainty_3p_MJBG = calculateMJBG(rQCD_pl3p, unc_rQCD_pl3p, fi_pl3p[18], fi_pl3p[19]) 
negative_lepton_1p_MJBG , negative_uncertainty_1p_MJBG = calculateMJBG(rQCD_nl1p, unc_rQCD_nl1p, fi_nl1p[18], fi_nl1p[19])
negative_lepton_3p_MJBG , negative_uncertainty_3p_MJBG = calculateMJBG(rQCD_nl3p, unc_rQCD_nl3p, fi_nl3p[18], fi_nl3p[19])

file.write("MJBG 1P Plus: "+ str(positive_lepton_1p_MJBG)+", "+str(positive_uncertainty_1p_MJBG)+"\n")
file.write("MJBG 3P Plus: "+ str(positive_lepton_3p_MJBG)+", "+str(positive_uncertainty_3p_MJBG)+"\n")

file.write("MJBG 1P Minus: "+ str(negative_lepton_1p_MJBG)+", "+str(negative_uncertainty_1p_MJBG)+"\n")
file.write("MJBG 3P Minus: "+ str(negative_lepton_3p_MJBG)+", "+str(negative_uncertainty_3p_MJBG)+"\n")

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

file.write("MJBG 1P: "+str(calculateAsymmetry(positive_lepton_1p_MJBG, positive_uncertainty_1p_MJBG, negative_lepton_1p_MJBG, negative_uncertainty_1p_MJBG))+"\n")
file.write("MJBG 3P: "+str(calculateAsymmetry(positive_lepton_3p_MJBG, positive_uncertainty_3p_MJBG, negative_lepton_3p_MJBG, negative_uncertainty_3p_MJBG))+"\n")
file.write("MJBG Tot: "+str(calculateAsymmetry(positive_lepton_MJBG, positive_uncertainty_MJBG, negative_lepton_MJBG, negative_uncertainty_MJBG))+"\n")

file.write("MC+MJBG 1P: "+str(calculateAsymmetry(pl1p_sum, np.sqrt(pl1p_unc_square), nl1p_sum, np.sqrt(nl1p_unc_square)))+"\n")
file.write("MC+MJBG 3P: "+str(calculateAsymmetry(pl3p_sum, np.sqrt(pl3p_unc_square), nl3p_sum, np.sqrt(nl3p_unc_square)))+"\n")
file.write("MC+MJBG Total: "+str(calculateAsymmetry(pl_sum, np.sqrt(pl_square_unc), nl_sum, np.sqrt(nl_square_unc)))+"\n")
file.close()
