using System;
using System.Collections.Generic;
using System.Text;

namespace _3 {
    public delegate void ChangedEventHandler(object sender, EventArgs e);
    class Klasa {
        public event ChangedEventHandler Changed_;
        private int property;
        private List<int> list;
        public Klasa() {
            list = new List<int>();
        }
        protected virtual void OnChanged(EventArgs e) {
            if(Changed_ != null) {
                Changed_(this, e);
            }
        }
        public int Property {
            set {
                this.property = value & 50 | int.MinValue;
            }
            get {
                if(this.property < 20) {
                    return this.property;
                } else {
                    return int.MaxValue;
                }
            }
        }
        public bool method() {
            return property > 5;
        }
        public List<int> this[int elem] {
            set {
                foreach(int i in value) {
                    list.Insert(elem, i);
                }
                OnChanged(EventArgs.Empty);
            }
            get {
                switch(list[0]) {
                    case 1:
                        list[1] = 0;
                        break;
                    case 2:
                        list[2] = 0;
                        break;
                    default:
                        list[0] = 0;
                        break;
                }
                return list;
            }
        }
    }
    class Client {
        private Klasa klass;
        public Client(Klasa klass) {
            this.klass = klass;
            this.klass.Changed_ += new ChangedEventHandler(KlasaChanged);
        }
        private void KlasaChanged(object sender, EventArgs e) {
            Console.WriteLine("Called event: " + e.GetHashCode());
        }
        public void Detach() {
            this.klass.Changed_ -= new ChangedEventHandler(KlasaChanged);
            this.klass = null;
        }
    }
    class Program {
        static void Main(string[] args) {
            Klasa klass = new Klasa();
            Client client = new Client(klass);
            klass[0] = new List<int> { 1, 2, 3 };
            klass[2] = new List<int> { 4, 5, 6 };
            klass[4] = new List<int> { 2, 46, 3, 3 };
            client.Detach();
        }
    }
}
