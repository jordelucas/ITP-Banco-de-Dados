# projetoBD-ITP

No SGBD ITP desenvolvido, foram inseridas todas as operações solicitadas, estando elas disponíveis em lista ordenada já no menu principal. São elas:

1- Criar tabela
2- Listar tabelas
3- Criar linha
4- Listar dados
5- Pesquisar valor
6- Apagar valor
7- Apagar Tabela

Contudo, na funcionalidade “Pesquisar valor”, caso o usuário solicite uma pesquisa de dados a partir de uma varável do tipo string, o sistema exibirá a seguinte mensagem: “Infelizmente a opção de pesquisa de strings não foi adicionada”, sendo este o único item obrigatório indisponível no SGBD.
O sistema não permitirá como entrada de dados: nomes de tabelas já existentes e chaves primárias de registros anteriores da mesma tabela. Para esses casos, serão exibidas mensagens informativas, bem como ao solicitar visualização, pesquisa, inserção de dados, entre outros, quando não houver tabelas armazenadas.
Durante o desenvolvimento, a ideia inicial de como seria a implementação do sistema sofreu diversas alterações. Por exemplo, não havia a ideia de utilizar três arquivos para armazenamento de dados, sendo dois deles definidos para cada tabela adicionada (“dados” e “tamanho”) e um em comum a todas (“tabelas”). No entanto, em determinado momento, notou-se a viabilidade desse método e como outros recursos da linguagem C seriam favorecidos, como o uso de struct, por exemplo.  Portanto, o desenvolvimento se deu como uma constante aprendizagem, onde o resultado final supre as necessidades de forma satisfatória. Logo, em um novo desenvolvimento eu não modificaria a implementação ou a distribuição das funções, mas adicionaria funcionalidades novas, como alteração de dados, pesquisas múltiplas e mais opções de pesquisa.
Para o funcionamento correto, além dos arquivos que se encontram na raiz do projeto, são necessárias três pastas:

- tabelas: encontra-se o arquivo “listaTabelas.txt”, onde serão armazenados os nomes das tabelas inseridas;
- dados: encontram-se vários arquivos que obedecem a nomenclatura ‘nome_da_tabela’+’_dados.txt’. Cada arquivo armazena os registros da respectiva tabela. Se não houver tabelas inseridas, a pasta estará vazia.
- tamanhos: encontram-se vários arquivos que obedecem a nomenclatura ‘nome_da_tabela’+’_tamanho.txt’. Cada arquivo armazena as colunas (nome e tipo de dado) da respectiva tabela. Se não houver tabelas inseridas, a pasta estará vazia.

Para compilar o projeto, aconselho o método utilizado em sala de aula. Estando com o GNU Compiler Collection (GCC) instalado na máquina e tendo identificado o arquivo que possui a função main (nomeado “principal.c”), basta executar o comando “gcc principal.c -o exe”, onde “exe” pode ser substituído por qualquer outro nome. Para executar o arquivo, usaremos “./exe”, ou outro nome definido no comando anterior.
Só foi utilizada a biblioteca padrão da linguagem C (stdio.h, string.h e stdlib.h). Não foram utilizadas bibliotecas externas.
Quanto a indentação, durante o desenvolvimento do projeto foi utilizado o editor de texto “Atom”. No github, em alguns trechos de código apareceram { } com pequenos recuos que não existiam no “Atom”.
