using System;
using System.Collections.Generic;
using System.Text;

namespace _3._2._2 {
    class BinaryTreeNode<T> {
        class DFSEnumerator : IEnumerator<T> {
            BinaryTreeNode<T> current;
            public DFSEnumerator(BinaryTreeNode<T> current) {
                this.current = current;
            }
            public bool MoveNext() {
                if(this.current.left != null) {
                    this.current = this.current.left;
                    return true;
                } else if(this.current.right != null) {
                    this.current = this.current.right;
                    return true;
                } else {
                    return false;
                }
            }
            public T Current {
                get {
                    return current.value;
                }
            }
            object System.Collections.IEnumerator.Current {
                get {
                    return this.Current;
                }
            }
            public void Reset() {
                this.current = null;
            }
            public void Dispose() {
            }
        }
        T value;
        public BinaryTreeNode<T> left;
        public BinaryTreeNode<T> right;
        public BinaryTreeNode(T value) {
            this.value = value;
        }
        public IEnumerator<T> GetEnumerator() {
            return new DFSEnumerator(this);
        }
    }
    class Program {
        static void Main(string[] args) {
            BinaryTreeNode<int> i = new BinaryTreeNode<int>(1);
            i.left = new BinaryTreeNode<int>(2);
            i.right = new BinaryTreeNode<int>(3);
            IEnumerator<int> en = i.GetEnumerator();
            Console.WriteLine(en.Current);
            en.MoveNext();
            Console.WriteLine(en.Current);
            en.MoveNext();
            Console.WriteLine(en.Current);
        }
    }
}
