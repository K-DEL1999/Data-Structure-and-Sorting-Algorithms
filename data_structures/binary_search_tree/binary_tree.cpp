#include <iostream>
#include "binary_tree.hpp"

int main(){
    int x;
    tree<int> H;
    
    for ( int i = 0; i < 10; i++ ){
        std::cin >> x;
        H.insert(x);
    }
    
    printf("Size of binary tree: %lu \n", H.size() );
    printf("Leaf nodes: %lu \n", H.leaves() );
    printf("Height of tree: %lu \n", H.height() );
    printf("Max value in tree: %i \n", H.max() );
    printf("Min value in tree: %i \n", H.min() );
    
    H.printPreorder();
    printf("\n");
    H.printPostorder();
    printf("\n");
    H.printInorder();
    printf("\n");
    
    if ( H.search(13) == true ){
        printf("HELLO\n\n");
        H.remove(13);
    }
    
    if ( H.search( 1001 ) == false ){
        std::cout << "1001 is not in the tree.! \n";
    }
    
    if (H.search(24) == true ){
        printf("HELLO\n\n");
        H.remove(24);
    }
    
    if ( H.search(56) == true ){
        printf("HELLO\n\n");
        H.remove(56);
    }
    
    std::cout << "Preorder \n";
    H.printPreorder();
    printf("\n");
    std::cout << "Postorder \n";
    H.printPostorder();
    printf("\n");
    std::cout << "Inorder \n";
    H.printInorder();
    printf("\n");

    H.clear();
    
    std::cout << "Preorder \n";
    H.printPreorder();
    printf("\n");
    std::cout << "Postorder \n";
    H.printPostorder();
    printf("\n");
    std::cout << "Inorder \n";
    H.printInorder();
    printf("\n");
    
    return 0;
}
