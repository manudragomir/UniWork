from testele.Test import Test
from repo.Repository import Repository
from valid.Validators import StudentValidator, LaboratorValidator
from consola.UI_console import Console
from business.Controllers import StudentControl, LaboratorControl

t = Test()
t.runtests()

repoStudenti = Repository()
repoLaborator = Repository()

validatorStudenti = StudentValidator()
validatorLaborator = LaboratorValidator()

controlStudenti = StudentControl(repoStudenti, validatorStudenti)
controlLaborator = LaboratorControl(repoLaborator, validatorLaborator)

cons = Console(controlStudenti, controlLaborator)
cons.run()