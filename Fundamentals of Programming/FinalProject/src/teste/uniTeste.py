from domain.entities import Student
from validare.Validator import StudentValidator
from business.Controllers import ServiceStudent
from repository.Repositories import RepoStudent
import unittest
from errors.erori import ValidError, RepoError

class TestCaseStudent(unittest.TestCase):
    def setUp(self):
        self.st1 = Student(12, "mihai", 215)
        self.st3 = Student(12, "gigi", 200)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
        
    def testGetName(self):
        self.assertEqual(self.st1.get_nume(), "mihai", "nume eronat")
        self.assertEqual(self.st3.get_nume(), "gigi", "nume gresit")
        
    def testGetId(self):
        self.assertTrue(self.st1.get_id() == 12)

class TestServiceStudent(unittest.TestCase):
    def setUp(self):
        self.val = StudentValidator()
        self.rep = RepoStudent()
        self.st_service = ServiceStudent(self.rep, self.val)
        
    def tearDown(self):
        unittest.TestCase.tearDown(self)
    
    def testServiceStudent(self):
        self.assertRaises(ValidError, self.st_service.addStudent, -1, "mihai", 215)
        stud = Student(12, "mircea", 200)
        self.rep.store_studenti(stud)
        self.assertRaises(RepoError, self.rep.store_studenti, stud)
