from testele.Test import Test
from repo.Repository import Repository
from valid.Validators import StudentValidator, LaboratorValidator, NotaValidator
from consola.UI_console import Console
from business.Controllers import StudentControl, LaboratorControl, NotaControl
import random

t = Test()
t.runtests()

repoStudenti = Repository()
repoLaborator = Repository()
repoNota = Repository()

validatorStudenti = StudentValidator()
validatorLaborator = LaboratorValidator()
validatorNota = NotaValidator()

controlStudenti = StudentControl(repoStudenti, validatorStudenti)
controlLaborator = LaboratorControl(repoLaborator, validatorLaborator)
controlNota = NotaControl(validatorNota, repoNota, repoStudenti, repoLaborator)

def getRandomString():
    string = ''
    alpha = 'abcdefghijklmnopqrstuvwxyz'
    j = random.randrange(1,30)
    for k in range(j):
        string += random.choice(alpha)
    return string

for i in range(10):
    idrnd = random.randrange(1,5000)
    stringrnd = getRandomString()
    grrnd = random.randrange(100,1000)
    controlStudenti.addStudent(idrnd, stringrnd, grrnd)
    
for i in range(10):
    nrlabrnd = random.randrange(1,10)
    nrlprbrnd = random.randrange(1,15)
    idrnd = random.randrange(1,5000)
    
    stringrnd = getRandomString()
        
    datarnd = ''
    datarnd += str(random.randrange(1,30))
    datarnd += '.'
    datarnd += str(random.randrange(1,12))
    datarnd += '.'
    datarnd += str(random.randrange(2000, 2018))
    controlLaborator.addLaborator(nrlabrnd, nrlprbrnd, stringrnd, datarnd)


cons = Console(controlStudenti, controlLaborator)
cons.run()