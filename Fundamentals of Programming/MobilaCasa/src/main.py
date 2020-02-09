'''
Created on Dec 10, 2018

@author: Manuel
'''

from infrastructure.Repository import RepoMobila
from business.GRASPControllers import ServMobila
from presentation.UI import Consola

#cream un obiect de tip RepoMobila
repoMobila = RepoMobila("mobila.txt")

#cream un obiect de tip ServMobila
servMobila = ServMobila(repoMobila)

c = Consola(servMobila)
c.run()