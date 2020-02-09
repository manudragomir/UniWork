'''
Created on Dec 9, 2018

@author: Manuel
'''
import unittest
from validators.Validare import ValidTriunghi, ValidError
from entities.triunghi import Triunghi

class TesteazaValidator(unittest.TestCase):
    def setUp(self):
        self.validator = ValidTriunghi()
        self.triunghi = Triunghi(3,4,5)
        self.btriunghi = Triunghi(2,3,8)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testValidator(self):
        self.assertRaises(ValidError, self.validator.valideazaTriunghi, self.btriunghi)
