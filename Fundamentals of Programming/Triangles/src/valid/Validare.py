from errors.Erori import ValidError

class ValidatorTriunghi(object):
    def valideazaTriunghi(self, triunghi):
        a = triunghi.get_l1()
        b = triunghi.get_l2()
        c = triunghi.get_l3()
        
        if a + b <= c:
            raise ValidError("Triunghi degenerat")
        
        if b + c <= a:
            raise ValidError("Triunghi degenerat")
        
        if a + c <= b:
            raise ValidError("Triunghi degenerat")