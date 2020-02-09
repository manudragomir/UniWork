'''
Created on Jan 29, 2019

@author: Manuel
'''
from infrastructure.Repository import RepoTriunghi
from business.GRASPControllers import ServTriunghi
from valid.Validare import ValidatorTriunghi
from presentation.UI import Consola

repoTriunghi = RepoTriunghi("triunghi.txt")

validTriunghi = ValidatorTriunghi()

servTriunghi = ServTriunghi(repoTriunghi, validTriunghi)

c = Consola(servTriunghi)

c.run()
