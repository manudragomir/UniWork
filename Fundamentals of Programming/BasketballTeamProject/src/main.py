'''
Created on Jan 31, 2019

@author: Manuel
'''

from infrastructure.Repository import RepoJucator
from validare.Validatori import ValidatorJucator
from business.GRASPControllers import ServJucator
from presentation.UI import Consola


repoJucator = RepoJucator("baschet.txt")
validJucator = ValidatorJucator()

servJucator = ServJucator(repoJucator, validJucator)

c = Consola(servJucator)

c.run()