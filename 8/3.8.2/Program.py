from System.Collections import Hashtable
from System.Collections.Generic import Dictionary

class HashTest(Hashtable):
    def __init__(self):
        for i in range(10):
            self.Add('key' + unicode(i), 'value' + unicode(i))
            print 'added', 'key' + unicode(i), ':', 'value' + unicode(i)
            
class DictTest(object):
    def __init__(self):
        self.dict = Dictionary[str, str]()
        for i in range(10):
            self.dict.Add('key' + unicode(i), 'value' + unicode(i))
            print 'added', 'key' + unicode(i), ':', 'value' + unicode(i)
        self.dict.Remove('key5')
        self.dict.Add('unknown key', 'unknown value')
    def iterate(self):
        for d in self.dict:
            print 'retrieved', d.Key, ':', d.Value

print "Hashtable:"
for h in HashTest():
    print 'retrieved', h.Key, ':', h.Value
        
print "\nDictionary:"
DictTest().iterate()