using System;
using System.Text;
using System.Runtime.InteropServices;

namespace lastlib {
    [GuidAttribute("8022D302-30F1-40FB-B550-B68424742B51")]
    public interface IPrimeTesterCS {
        [DispId(1)] int IsPrime(int number);
    }
    [GuidAttribute("BF029E42-CDBD-4EFF-8120-AE486C64E4DB")]
    [ClassInterface(ClassInterfaceType.None)]
    [ProgId("PrimeTesterCS")] // for eventual late binding
    public class PrimeTesterCS : IPrimeTesterCS {
        public int IsPrime(int number) {
            for(int i = 2; i * 2 < number; ++i) {
                if(number % i == 0) {
                    return -1;
                }
            }
            return 0;
        }
    }
}
