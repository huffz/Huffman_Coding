void test_build_hash()
{
	hash_tree *new = create_hash();
	node *test = create_node('x', 10, NULL, NULL);
	stack *stacktree = criars();
	build_hash(test, new, stacktree);
	CU_ASSERT(((element *)new->trees['x']) != NULL);
	CU_ASSERT(new != NULL);
	CU_ASSERT(test != NULL);
	CU_ASSERT(stacktree != NULL);

}
void teste_eraseHash()
{
	hash_tree *new = create_hash();
	CU_ASSERT(new != NULL);
	((element *)new->trees[0]->key) = 1;
	CU_ASSERT(((element *)new->trees[0])] != NULL);
	eraseHash(new);
	CU_ASSERT(((element *)new->trees[0]) == NULL);

}
if (NULL == CU_add_test(pSuite, "test - 7", test_build_hash)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
if (NULL == CU_add_test(pSuite, "test - 8", teste_eraseHash)) {
		CU_cleanup_registry();
		return CU_get_error();
	}
