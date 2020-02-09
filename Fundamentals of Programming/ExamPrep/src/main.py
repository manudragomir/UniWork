'''
Created on Dec 8, 2018

@author: Manuel
'''

from infrastracture.Repository import RepoTriunghi
from validators.Validare import ValidTriunghi
from graspcontrollers.Service import ServTriunghi
from ui.Consola import Console

repoTriunghi = RepoTriunghi("triunghi.txt")
validTriunghi = ValidTriunghi()

servTriunghi = ServTriunghi(repoTriunghi, validTriunghi)
c = Console(servTriunghi)

c.run()