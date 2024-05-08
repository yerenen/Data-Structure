/*
* 8 查找
* 8.2 树表的查找
* 8.2.5 平衡二叉树
* --问题：如何提高形态不均衡的二叉排序树的查找效率？
* 解决办法：做“平衡化”处理，即尽量让二叉树的形状均衡！——平衡二叉树！！
* --定义：
* 平衡二叉树（balanced binary tree）又称为AVL树（Adelson-Velskii and Landis）
* 一棵平衡二叉树或是空树，或者是具有下列性质的二叉排序树：
* ①左子树与右子树的高度之差的绝对值小于等于1
* ②左子树和右子树也是平衡二叉排序树
* 为了方便起见，给每个结点附加一个数字，给出该结点左子树与右子树的高度差，这个数字称为结点的平衡因子（BF）
* 平衡因子 = 结点左子树的高度 - 结点右子树的高度
* BF = -1/0/1
* 对于一棵有n个结点的AVL树，其高度保持在O(log2n)数量级，ASL也保持在O(log2n)量级
* --失衡二叉排序树的分析与调整：
* 平衡调整的四种类型：LL型、LR型、RL型、RR型
* 调整原则：
* ①降低高度
* ②保持二叉排序树性质
* (我理解，所谓调整即最小放左边，最大放右边)
* （注意：每次调整最小的那颗子树）
*/