#ifndef ERRELATIONSDATA_H
#define ERRELATIONSDATA_H

#include <QString>
#include <QDebug>
#include <QList>
#include <tuple>
#include <Support.h>
#include <QJsonArray>
#include <QJsonObject>
#include <ConsoleOutput.h>

/**
 * @brief The ERRelationsData class
	описывает связи диаграммы
 */
class ERRelationsData
{
	public:
		ERRelationsData();

		/**
		 * @brief deleteRelation
		 *	удаляет данные о связи
		 * @param first
		 *	участник связи
		 * @param second
		 *	участник связи
		 * @return
		 *	true удалил
		 *	false не удалил
		 */
		bool deleteRelation(QString first, QString second);

		/**
		 * @brief addRelation
		 *	добавляет связь
		 * @param first
		 *	участник связи
		 * @param second
		 *	участник связи
		 * @param cordinalityFirst
		 *	кардинальность от 1 к 2
		 * @param cordinalitySecond
		 * *	кардинальность от 2 к 1
		 * @return
		 *	true добавил
		 *	false нет не добавил
		 */
		int addRelation(QString first, QString second, int cordinalityFirst, int cordinalitySecond);

		/**
		 * @brief getAllAjasencyFor
		 *	получает список смежности для id
		 * @param id
		 *	имя сущности для которой производится поиск
		 * @return
		 *	получает список смежности и кардинальсности
		 */
		QList<std::tuple<QString, QString, int, int>> getAllAjasencyFor(QString id);

		/**
		 * @brief getAjasencyByName
		 *	получает список смежности для id
		 * @param id
		 *	имя сущности для которой производится поиск
		 * @return
		 *	получает список смежности
		 */
        QList<QString> getAjasencyByName(QString id) const;

		/**
		 * @brief isExist
		 *	проверяет есть ли такая связь
		 * @param first
		 *	участник 1
		 * @param second
		 *	участник 2
		 * @return
		 *	true exist
		 *	false not exist
		 */
		bool isExist(QString first, QString second);

		/**
		 * @brief renameEssence
		 *	переименовывает сущность во всех связах
		 * @param old_name
		 * @param new_name
		 * @return
		 *	true переименовал
		 *	false not renamed
		 */
		bool renameEssence(QString old_name, QString new_name);

		/**
		 * @brief setCord
		 *	устанавливает кардинальность на связь
		 * @param A
		 *	участник 1
		 * @param B
		 *	участник 2
		 * @param cord_a
		 *	кардинальность от 1 к 2
		 * @param cord_b
		 *	кардинальность от 2 к 1
		 * @return
		 *	true установил
		 *	false нет
		 */
		bool setCord(QString A, QString B, int cord_a, int cord_b);

		/**
		 * @brief getCordinality_table
		 *	вернёт всю таблицу связей
		 * @return
		 */
		QList<std::tuple<QString, QString, int, int> > getCordinality_table() const;

		/**
		 * @brief clear
		 *	удаление всего @see cordinality_table
		 */
		void clear();

		//фацловые операции
		void write(QJsonObject &json) const;
		void read(const QJsonObject &json);

		//debug ptrint in terminal
		void print();
		void printList(QList<std::tuple<QString, QString, int, int>> list);
private:
		QList<std::tuple<QString, QString, int, int>> cordinality_table;
};

#endif // ERRELATIONSDATA_H
