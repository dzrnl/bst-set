# BST Set

Бинарное дерево поиска. Шаблоны. STL.

## Задача

Реализовать три STL-совместимых контейнера для [BinarySearchTree](https://en.wikipedia.org/wiki/Binary_search_tree),
реализующие различные [способы обхода дерева (in-, pre-, post-order)](https://en.wikipedia.org/wiki/Tree_traversal)
через итератор.

## Требования

Контейнер должен предоставлять из себя шаблон, параметризуемый типом хранимых объектов, оператором сравнения и
аллокатором, а так же удовлетворять следующим требованиям к stl - совместимым контейнерам:

- [контейнера](https://en.cppreference.com/w/cpp/named_req/Container)
- [ассоциативный контейнера](https://en.cppreference.com/w/cpp/named_req/AssociativeContainer)
- [контейнера с обратным итератором](https://en.cppreference.com/w/cpp/named_req/ReversibleContainer)
- [контейнера поддерживающие аллокатор](https://en.cppreference.com/w/cpp/named_req/AllocatorAwareContainer)
- [обладать двунаправленным итератором](https://en.cppreference.com/w/cpp/named_req/BidirectionalIterator)

Способ обхода дерева должен быть реализован через итератор, те оператор "++" должен приводить к перемещению итератора к
следующему элементу в дереве, согласно правилу обхода.

## Тесты

Все вышеуказанные требования должны быть покрыты тестами, с помощью
фреймворка [Google Test](http://google.github.io/googletest).

## Ограничения

- Запрещено использовать стандартные контейнеры

## NB

Рекомендуется не создавать три отдельных контейнера, а вместо этого
использовать [Tag Dispatch Idiom](https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Tag_Dispatching).
