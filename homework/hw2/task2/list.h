#pragma once
#include "listnode.h"

 template <typename T> class List { //�б�ģ����
	
 private:
	    Rank _size; 
        ListNodePosi(T) header;
        ListNodePosi(T) trailer;//��ģ��ͷ�ڱ���β�ڱ�
	
 protected:
	    void init(); //�б���ʱ�ĳ�ʼ��
	    Rank clear(); //������нڵ�
	    void copyNodes(ListNodePosi<T>, Rank); //�����б�����λ��p���n��
	    ListNodePosi<T> merge(ListNodePosi<T>, Rank, List<T>&, ListNodePosi<T>, Rank); //�鲢
	    void mergeSort(ListNodePosi<T>&, Rank); //�Դ�p��ʼ������n���ڵ�鲢����
	    void selectionSort(ListNodePosi<T>, Rank); //�Դ�p��ʼ������n���ڵ�ѡ������
	    void insertionSort(ListNodePosi<T>, Rank); //�Դ�p��ʼ������n���ڵ��������
	    void radixSort(ListNodePosi<T>, Rank); //�Դ�p��ʼ������n���ڵ��������
	
 public:
	 // ���캯��
		    List() { init(); } //Ĭ��
	    List(List<T> const& L); //���帴���б�L
	    List(List<T> const& L, Rank r, Rank n); //�����б�L���Ե�r�����n��
	   List(ListNodePosi<T> p, Rank n); //�����б�����λ��p���n��
	    // ��������
		   ~List(); //�ͷţ�����ͷ��β�ڱ����ڵģ����нڵ�
	// ֻ�����ʽӿ�
		    Rank size() const { return _size; } //��ģ
	   bool empty() const { return _size <= 0; } //�п�
	    ListNodePosi<T> operator[](Rank r) const; //���أ�֧��ѭ�ȷ��ʣ�Ч�ʵͣ�
	    ListNodePosi<T> first() const { return header->succ; } //�׽ڵ�λ��
	    ListNodePosi<T> last() const { return trailer->pred; } //ĩ�ڵ�λ��
	   bool valid(ListNodePosi<T> p) //�ж�λ��p�Ƿ����Ϸ�
		  { return p && (trailer != p) && (header != p); } //��ͷ��β�ڵ��ͬ��NULL
	    ListNodePosi<T> find(T const& e) const //�����б����
		   { return find(e, _size, trailer); }
	    ListNodePosi<T> find(T const& e, Rank n, ListNodePosi<T> p) const; //�����������
	    ListNodePosi<T> search(T const& e) const //�����б����
	    { return search(e, _size, trailer); }
		ListNodePosi<T> search(T const& e, Rank n, ListNodePosi<T> p) const; //�����������
		ListNodePosi<T> selectMax(ListNodePosi<T> p, Rank n); //��p����n-1�������ѡ�������
		ListNodePosi<T> selectMax() { return selectMax(header->succ, _size); } //���������
 // ��д���ʽӿ�
		    ListNodePosi<T> insertAsFirst(T const& e); //��e�����׽ڵ����
	    ListNodePosi<T> insertAsLast(T const& e); //��e����ĩ�ڵ����
	    ListNodePosi<T> insert(ListNodePosi<T> p, T const& e); //��e����p�ĺ�̲���
	    ListNodePosi<T> insert(T const& e, ListNodePosi<T> p); //��e����p��ǰ������
	    T remove(ListNodePosi<T> p); //ɾ���Ϸ�λ��p���Ľڵ�,���ر�ɾ���ڵ�
	    void merge(List<T>& L) { merge(header->succ, _size, L, L.header->succ, L._size); } //ȫ�б�鲢
	    void sort(ListNodePosi<T>, Rank); //�б���������
	    void sort() { sort(first(), _size); } //�б���������
	    Rank deduplicate(); //����ȥ��
	    Rank uniquify(); //����ȥ��
	    void reverse(); //ǰ���ã�ϰ�⣩
	 // ����
		    void traverse(void (*)(T&)); //����ʵʩvisit����������ָ�룩
	   template <typename VST> void traverse(VST&); //����ʵʩvisit��������������
	
}; //List


 template <typename T>
 void List<T>::init()
 {
     header = new ListNode<T>;
     trailer = new ListNode<T>;
     header->succ = trailer;
     header->pred = NULL;
     trailer->pred = header;
     trailer->succ = NULL;
     _size = 0;
 }

 template <typename T> // �����±����������ͨ����ֱ��ڪ���б�ڵ㣨��ڱ㣬Ч�ʵͣ������ã�
 T& List<T>::operator[](Rank r) const
 {                                // assert: 0 <= r < size
     ListNodePosi(T) p = first(); // ���׽ڵ����
     while (0 < r--)
         p = p->succ; // ˳����r���ڵ㼴��
     return p->data;  // Ŀ��ڵ㣬ކ����������Ԫ��
 }

 template <typename T>
 ListNodePosi(T) List<T>::insertAsFirst(T const& e)
 {
     _size++;
     return header->insertAsSucc(e);
 }
 template <typename T>
 ListNodePosi(T) List<T>::insertAsLast(T const& e)
 {
     _size++;
     return trailer->insertAsPred(e);
 }

 template <typename T>
 ListNodePosi(T) List<T>::insertA(ListNodePosi(T) p, T const& e)
 {
     _size++;
     return p->insertAsSucc(e);
 }
 template <typename T>
 ListNodePosi(T) List<T>::insertB(ListNodePosi(T) p, T const& e)
 {
     _size++;
     return p->insertAsPred(e);
 }
 template <typename T> // ��e������ǰ�ڵ�Tǰ�I��ء��ǰ�ڵ������б�ک���ڱ�ͷ�ڵ�header��
 ListNodePosi(T) ListNode<T>::insertAsPred(T const& e)
 {
     ListNodePosi(T) x = new ListNode(e, pred, this); // �����½ڵ�
     pred->succ = x;
     pred = x; // ک����������
     return x; // ކ���½ڵ�mλ��
 }
 template <typename T> // ��e������ǰ�ڵ�T��I��ء��ǰ�ڵ������б�ک���ڱ�β�ڵ�trailer��
 ListNodePosi(T) ListNode<T>::insertAsSucc(T const& e)
 {
     ListNodePosi(T) x = new ListNode(e, this, succ); // �����½ڵ�
     succ->pred = x;
     succ = x; // ک����������
     return x; // ކ���½ڵ�mλ��
 }

 template <typename T> // �б��ڲ��ڷ������c�б�����λ��p��mn��
 void List<T>::copyNodes(ListNodePosi(T) p, int n)
 {           // p�Ϸ�����������n-1�����̽ڵ�
     init(); // ����ͷ��β�ڱ��ڵ�����_ʼ��
     while (n--)
     {
         insertAsLast(p->data);
         p = p->succ;
     } // ������p�mn��������Ϊĩ�ڵ�I��
 }

 template <typename T> // ���c�б�����λ��p��mn�assert: pΪ�Ϸ�λ�ã���������n-1����̽ڵ㣩
 List<T>::List(ListNodePosi(T) p, int n)
 {
     copyNodes(p, n);
 }
 template <typename T> // ���帴�c�б�L
 List<T>::List(List<T> const& L)
 {
     copyNodes(L.first(), L._size);
 }
 template <typename T> // ���cL���Ե�r����mn�assert: r+n <= L._size��
 List<T>::List(List<T> const& L, int r, int n)
 {
     copyNodes(L[r], n);
 }
 template <typename T>
 T List<T>::remove(ListNodePosi(T) p)
 {                  // �����Ϸ��ڵ�p��ކ������ֵ
     T e = p->data; // �����������ڵ�m��ֵ���ٶ�T���Ϳ�ֱ�Ӹ�ֵ��
     p->pred->succ = p->succ;
     p->succ->pred = p->pred; // ��̡�ǰ��
     delete p;
     _size--;  // �ͷŽڵ㣬�����_ģ
     return e; // ކ�ر����m��ֵ
 }
 template <typename T>
 List<T>::~List()
 {
     clear();
     delete header;
     delete trailer;
 }
 template <typename T>
 int List<T>::clear()
 {
     int oldSize = _size;
     while (0 < _size)
         remove(header->succ); // ���������׽ڵ㣬ֱ���б���
     return oldSize;
 }

 template <typename T>
 int List<T>::deduplicate()
 { // �޳������б��аm�ظ��ڵ�
     if (_size < 2)
         return 0;        // ƽ���б���Ȼ���ظ�
     int oldSize = _size; // �Ǐ�ԭ�_ģ
     ListNodePosi(T) p = header;
     Rank r = 0; // p���׽ڵ㿪ʼ
     while (trailer != (p = p->succ))
     {                                            // ����ֱ�bĩ�ڵ�
         ListNodePosi(T) q = find(p->data, r, p); // ��p�mr�����棩ǰ���в�����ͬ��
         q ? remove(q) : r++;                     // ���mȷ���ڣ�������T�������ȼ�һ
     }                                            // assert: ѭ�������аm����ʱ�̣�p�m����ǰ����آ��ͬ
     return oldSize - _size;                      // �б��_ģ����������������Ԫ������
 }

 template <typename T>
 void List<T>::traverse(void (*visit)(T&)) // ���Ӻ���ָ����c����
 {
     for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
         visit(p->data);
 }
 template <typename T>
 template <typename VST>            // Ԫ�����͡�������
 void List<T>::traverse(VST& visit) // ���Ӻ���������c����
 {
     for (ListNodePosi(T) p = header->succ; p != trailer; p = p->succ)
         visit(p->data);
 }
 template <typename T>
 int List<T>::uniquify()
 { // �����޳��ظ�Ԫ�أ�Ч�ʸ���
     if (_size < 2)
         return 0;        // ƽ���б���Ȼ���ظ�
     int oldSize = _size; // �Ǐ�ԭ�_ģ
     ListNodePosi(T) p = first();
     ListNodePosi(T) q;               // pΪ���ך���㣬qΪ����
     while (trailer != (q = p->succ)) // ����������ڰm�ڵ��(p, q)
         if (p->data != q->data)
             p = q; // �����죬��ת����һ�ך�
         else
             remove(q);      // ������ͬ������������
     return oldSize - _size; // �б��_ģ����������������Ԫ������
 }

 template <typename T> // �������б��ڽڵ�p��������trailer���mn�����棩ǰ���У��҄bآ��ءe�m�����
 ListNodePosi(T) List<T>::search(T const& e, int n, ListNodePosi(T) p) const
 {                    // assert: 0 <= n <= rank(p) < _size
     while (0 <= n--) // ��ءp�m����mn��ǰ����������������Ƚ�
         if (((p = p->pred)->data) <= e)
             break; // ֱ�����С���ֵԽ��䷶ΧԽ��                                         // assert: ����λ��p�ط������ѯدԼ���������ܴ�ǰ���һ�΃̼���ȽϿ���û����د����Чء��-inf�Ƚϣ�
     return p;      // ކ�ز�����ֹ�mλ��
 } // ʧ��ʱ��ކ�س׼���߽�mǰ����������header�����������߿�ͨ��valid()�`�ϳɹ�����

 template <typename T>
 void List<T>::sort(ListNodePosi(T) p, int n)
 { // �б�׼�����
     switch (rand() % 3)
     { // ���ѡ�������㷨���ɸ��ݾ�������m�ص����ѡ��������
     case 1:
         insertionSort(p, n);
         break; // �I������
     case 2:
         selectionSort(p, n);
         break; // ѡ������
     default:
         mergeSort(p, n);
         break; // ��������
     }
 }

 template <typename T> // �б�m�I�������㷨������ʼءλ��p�mn��Ԫ������
 void List<T>::insertionSort(ListNodePosi(T) p, int n)
 { // valid(p) && rank(p) + n <= size
     for (int r = 0; r < n; r++)
     {                                            // ��һΪ���ڵ�
         insertA(search(p->data, r, p), p->data); // ���������mλ�ÎԓI��
         p = p->succ;
         remove(p->pred); // ת����һ�ڵ�
     }
 }

 template <typename T> // �б�mѡ�������㷨������ʼءλ��p�mn��Ԫ������
 void List<T>::selectionSort(ListNodePosi(T) p, int n)
 { // valid(p) && rank(p) + n <= size
     ListNodePosi(T) head = p->pred;
     ListNodePosi(T) tail = p;
     for (int i = 0; i < n; i++)
         tail = tail->succ; // ������׼�Ϊ(head, tail)
     while (1 < n)
     {                                                   // ��������ʣ�����ڵ�Tǰ���ڴ�����׼���
         ListNodePosi(T) max = selectMax(head->succ, n); // �ҳ�����ߣ���دʱ�������ȣ�
         insertB(tail, remove(max));                     // ���䶂������׼�ĩβ����Ϊ����׼��°m��Ԫ�أ�
         tail = tail->pred;
         n--;
     }
 }

 template <typename T> // ����ʼءλ��p�mn��Ԫ����ѡ�������
 ListNodePosi(T) List<T>::selectMax(ListNodePosi(T) p, int n)
 {
     ListNodePosi(T) max = p;                         // ������ݶ�Ϊ�׽ڵ�p
     for (ListNodePosi(T) cur = p; 1 < n; n--)        // ���׽ڵ�p�������������ڵ���һ��max�Ƚ�
         if (!lt((cur = cur->succ)->data, max->data)) // ����ǰԪ��آСءmax����
             max = cur;                               // �������Ԫ��λ�üǏ�
     return max;                                      // ކ�����ڵ�λ��
 }

 template <typename T> //
 void List<T>::merge(ListNodePosi(T)& p, int n, List<T>& L, ListNodePosi(T) q, int m)
 {                                            // assert: this.valid(p) && rank(p) + n <= size && this.sorted(p, n)
                                              // L.valid(q) && rank(q) + m <= L._size && L.sorted(q, m)
                                              // ע�⣺�ڏ�������T��m���ϣ��п��� this == L && rank(p) + n = rank(q)
     ListNodePosi(T) pp = p->pred;            // ����ǰ����������header�����Ա�ކ��ǰ ...
     while (0 < m)                            // ��q��δ�����׼�Tǰ
         if ((0 < n) && (p->data <= q->data)) // ��p���ڳ׼�����v(p) <= v(q)����

         {
             if (q == (p = p->succ))
                 break;
             n--;
         }    // p����ώ԰m�б����滻Ϊ��ֱ�Ӻ��
         else // ��p�ѳ����ҽ��v(q) < v(p)����

         {
             insertB(p, L.remove((q = q->succ)->pred));
             m--;
         }         // ��qת����p�Tǰ
     p = pp->succ; // ȷ�����Ժ�׼�m���£����
 }

 template <typename T> // �б�m���������㷨������ʼءλ��p�mn��Ԫ������
 void List<T>::mergeSort(ListNodePosi(T)& p, int n)
 { // valid(p) && rank(p) + n <= size
     if (n < 2)
         return;     // ��������Χ���㹻С����ֱ��ކ�أ�����...
     int m = n >> 1; // ���е�Ϊ��
     ListNodePosi(T) q = p;
     for (int i = 0; i < m; i++)
         q = q->succ; // �����б�
     mergeSort(p, m);
     mergeSort(q, n - m);          // ��ǰ�������б��ɾ����
     merge(p, m, *this, q, n - m); // ����
 } // ע�⣺�����p��Ȼָ�򏌎Ժ�׼�m���£����