import numpy as np
import matplotlib.pyplot as plt
import scipy as sc
import pandas as pd
import math as mt
import ROOT
import os
import random
from array import array
from ROOT import TCanvas, gStyle, TFile, TProfile, TNtuple, TH1D, TH2D, TH3D, TGraph, TMultiGraph, TPad, THStack, TH1F, TLegend, gROOT

def Testt(alpha, beta):
    print(alpha+beta)

def plotRoot1DHistogram():
    DataFile = ROOT.TFile("/home/fardousr/Desktop/Output/Convergent_Data/High energy 350MeV/Energy_350_Alpha:_10._Beta:_1010.mm_Sigma_15.mm.root")
    hist = DataFile.Get('ProtonEnergyHisto').Project3D("yz")
    can1 = TCanvas( 'c1', 'Deterministic LET', 200, 10, 2400, 1500)
    can1 = TCanvas( 'can1', 'Longitudinal Energy Deposition by All Partiicles', 800, 500 )
    can1.SetFillColor( 19 )
    can1.GetFrame().SetFillColor( 21 )
    can1.GetFrame().SetBorderSize( 6 )
    can1.GetFrame().SetBorderMode( -1 )
    hist.GetXaxis().SetTitle("Depth [mm]");
    hist.GetYaxis().SetTitle("Energy [eV]");
    hist.Draw()
    hist.GetXaxis().CenterTitle();
    hist.GetYaxis().CenterTitle();
    hist.GetXaxis().SetRangeUser(0, 180);
    hist.GetYaxis().SetRangeUser(-50, 50);
    hist.Draw("COLZ")
    gStyle.SetPalette(1)
    hist.SetStats(0)
    can1.Modified()
    can1.Update()
    return(can1)
    can1.Print("TestFunction.png");

def BraggPeakEnergyList(min, max, numBeam):
    alpha = 1.9*10**-3
    p = 1.8
    depthStep = (max-min)/(numBeam-1)
    depth = np.arange(min, max, depthStep)
    depth = np.append(depth, max)
    energy = (depth/alpha)**(1/p)
    return energy

def Energy2Range(E):
    alpha = 1.9*10**-3
    p = 1.8
    proton_range = alpha*E**p
    return(proton_range)

def Range2Energy(R):
    alpha = 1.9*10**-3
    p = 1.8
    energy = (R/alpha)**(1/p)
    return(energy)

def RBEMatrix(file):
    RBE_min = 1
    c = 3.76
    dose_radius = 50/1000
    DataFile = ROOT.TFile(file)
    Energy_XZ = DataFile.Get('ProtonEnergyHisto').Project3D("XZ")
    Energy_ZZ = DataFile.Get('ProtonEnergyHisto').Project3D("Z")
    LETData   = DataFile.Get('LETDataHisto')
    LET       = LETData/(Energy_ZZ*1000000)

    RBE      = array( 'd' )
    depth    = array( 'd' )

    for j in range(1, 801):
        Energy = Energy_ZZ.GetBinContent(j)* 1.60218e-19
        Mass = mt.pi*dose_radius**2*Energy_ZZ.GetBinWidth(j)*997
        Dose = Energy/Mass
        LET_value = LET.GetBinContent(j)
        RBE_max_value = 0.892 + (0.179*LET_value)

        RBE_value = 1/(2*Dose)*(mt.sqrt(c**2 +(4*Dose*c*RBE_max_value)+(4*Dose**2*RBE_min**2)) -c)
        RBE.append(RBE_value)
        depth.append(LET.GetXaxis().GetBinCenter(j))

    RBE2D = TH2D("LET2D", "LET2D", 800, 0, 200, 200, 0, 50)

    for i in range(1,801):
        y=RBE[i-1]
        for j in range(1, 201):
            RBE2D.SetBinContent(i,j, y)

    RBE = RBE2D.Clone()
    RBE.SetDirectory(0)
    return RBE;
