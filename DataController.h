#ifndef DATACONTROLLER_H
#define DATACONTROLLER_H

#include <QObject>
#include <QList>
#include <QString>
#include <EREssenceData.h>
#include <ERRelationsData.h>
#include <QRegExp>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QByteArray>
#include <ConsoleOutput.h>

/**
 * @brief The DataController class
 * Описывает логику поведение ER и Data моделей
 */
class DataController
{
	public:

		static DataController * getInstance();

		QList<std::tuple<QString, QString, int, int> > getRelationTable();

		/**
		 * @brief createEssence
		 *	Создаёт сущность, с учетом правил построения ER модели
		 * @param id
		 *	имя сущности
		 * @param type
		 *	тип сущности
		 * @param keys
		 *	ключи сущности
		 * @param attributes
		 *	атрибуты сущности
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int createEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);

		/**
		 * @brief removeEssence
		 *	удалит сущность по id
		 * @param id
		 *	имя сущности
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 *
		 */
		int removeEssence(QString id);

		/**
		 * @brief createRelation
		 *	создаёт связь, или простую или сущность ассоциацию, зависит от типов first and second
		 * @param id_first
		 *	имя первой сущности
		 * @param id_second
		 *	имя второй сущности
		 * @param cord_one
		 *	карданальность от 1 -> 2
		 * @param cord_two
		 *	*	карданальность от 2 -> 1
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int createRelation(QString id_first, QString id_second, int cord_one, int cord_two);

		/**
		 * @brief removeRelation
		 *	удаляет связь
		 * @param id_first
		 *	имя первой сущности учавствующей в связи
		 * @param id_second
		 *	имя второй сущности учавствующей в связи
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int removeRelation(QString id_first, QString id_second);

		/**
		 * @brief removeAttribute
		 *	удаляет существующий атрибут
		 * @param id
		 *	имя сущности с атрибутом
		 * @param attr_name
		 *	имя атрибута
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int removeAttribute(QString id, QString attr_name);

		/**
		 * @brief addAttribute
		 *	вставляет в сущность атрибут
		 * @param id
		 *	имя сущности для вставки атрибута
		 * @param attr_name
		 *	имя атрибута
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int addAttribute(QString id, QString attr_name);

		/**
		 * @brief removeKey
		 * Удаляет ключ из сущности
		 * @param id
		 * имя сущности
		 * @param key_name
		 *	имя ключа
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int removeKey(QString id, QString key_name);

		/**
		 * @brief addKey
		 * вставляет ключ в сущность
		 * @param id
		 *	имя сущности для вставки
		 * @param key_name
		 *	имя ключа
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int addKey(QString id, QString key_name);

		/**
		 * @brief joinBaseToExistAssociation
		 *	производит включание сущности в состав ассоциации
		 * @param essence
		 *	стержевая сущность
		 * @param association
		 *	ассациация
		 * @param cord
		 *	кардинальность от essence to association
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int joinBaseToExistAssociation(QString essence, QString association, int cord);

		/**
		 * @brief setCordinality
		 * устанавлявает кардинальнолсть между а и б
		 * @param id_a
		 *	имя первой сущности
		 * @param id_b
		 *	имя второй сущности
		 * @param cord_A
		 *	кардинальность от а к б
		 * @param cord_B
		 *	карданальность от б к а
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 *
		 */
		int setCordinality(QString id_a, QString id_b, int cord_A, int cord_B);

		/**
		 * @brief renameEssence
		 *	переименует сущность
		 * @param id_to_rename
		 *	имя сущности для переименования
		 * @param new_id
		 *	новое имя
		 * @return
		 *	0 если все хорошо
		 *	!0 если что то пошло не так
		 */
		int renameEssence(QString id_to_rename, QString new_id);

		//debug - in terminal
		void printAllEssence();
		void printEssenceByID(QString id);
		void printRelations();

		/**
		 * @brief getConnectionAttributesFor
		 *	расчитывает положение атрибута или ключа в массиве ключей или атрибутов
		 * std::tuple<QString, int, int, QString, int, int>
		 *	Имя первого, позиция первого в таблице, тоже и для вторго.
		 * @param id_first
		 *	имя первой сущности
		 * @param id_second
		 *	имя второй сущности
		 * @return
		 *	std::tuple<QString, int, int, QString, int, int>
		 *	Имя первого, позиция первого в таблице, тоже и для вторго.
		 */
		std::tuple<QString, int, QString, int> getConnectionAttributesFor(QString id_first, QString id_second);

		/**
		 * @brief getEssences
		 *	вернёт список имен всех сущностей диаграммы
		 * @return
		 */
		QList<QString> getEssences();

		/**
		 * @brief getProperties
		 * вернет ключи соотвествено mode
		 * @param mode	1 - ключи единоличные - красные
		 *				2 - свойства - белые
		 *				3 - ключи составные
		 *
		 * @return
		 *	список имен свойств
		 */
		QList<QString> getProperties(QString id, int mode);

		/**
		 * @brief getAjesencyFor
		 * @param id
		 *	имя сущности
		 * @return
		 *	вернёт список смежных сущностей к id
		 */
        QList<QString> getAjesencyFor(QString id) const;

		/**
		 * @brief search
		 * @param id
		 *	имя сущности
		 * @return
		 * вернёт указатель на сущность
		 * или nullptr id not exist
		 */
		EREssenceData * search(QString id);

		/**
		 * @brief saveState
		 *	сохраняет класс на диск
		 * @param path
		 *	путь для сохранения
		 * @return
		 *	true если сохранил
		 *	false если нет
		 */
		bool saveState(QString path);

		/**
		 * @brief loadState
		 *	загружает класс с диска
		 * @param path
		 *	путь к файлу
		 * @return
		 *	true если сохранил
		 *	false если нет
		 */
		bool loadState(QString path);

		/**
		 * @brief clear
		 *	отчищает все списки и связи диаграммы
		 *	это подготовка к загрузке нового файла или отчистка при создании пустого
		 */
		void clear();


        /**
         * @brief checkPermittionToSave
         *  Проверяет можно ли сохранить файл.
         *  Допустим файл нельзя соханить если есть висячие сущности
         * @return
         *  true если можно производить сохрание
         *  false если нельзя
         */
        bool saveIsPermit() const;
	private:
		void read(const QJsonObject &json);
		void write(QJsonObject &json) const;
		DataController();
		DataController(DataController const&){}
		DataController& operator=(DataController const&){}
		static DataController * self;

		//checks
		int checkBeforeCreationEssence(QString id, int type, QList<QString> keys, QList<QString> attributes);
		int checkBeforeCreationRelation(QString id_first, QString id_second, int cord_one, int cord_two);

		bool essenceIsExist(QString id);
		bool relationIsExist(QString id_first, QString id_second);

		bool keyISattr(QList<QString> keys, QList<QString> attributes);
		bool keyOrAttributeIsExist(QList<QString> keys, QList<QString> attrs);
		bool keyOrAttributeDublication(QList<QString> keys, QList<QString> attrs);
		bool keyOrAttributeIsNameOfEssence(QString id, QList<QString> keys = QList<QString>(), QList<QString> attrs = QList<QString>());

		bool oneOfTwoIs(int type_first, int type_second, int condition_type);
		int checkCordinality(QString first, QString second, int first_type, int second_type, int &cord_first, int &cord_second);

		//to perform action
		void insertKeyInCharacteristic(EREssenceData * e, QString key);
		void insertKeyInDesignation(EREssenceData * e, QString key);
		void insertKeyInBase(EREssenceData * e, QString key);
		void insertKeyInAssociation(EREssenceData * e, QString key);

		int createRelationBetweenBaseAndDesignation(			EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenBaseAndCharacteristic(			EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweeAssociationAndDesignation(		EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenAssociationAndCharacteristic(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenBaseAndBaseWithNewRelation(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);
		int createRelationBetweenDesignationAndCharacteristic(	EREssenceData * e1, EREssenceData * e2, int cord_one, int cord_two);


		int removeRelationBetweenEssences(EREssenceData * e1, EREssenceData * e2);
		int removeRelationBetweenBaseAndDesignation(EREssenceData * e1, EREssenceData * e2);

		int removeKeyFrom(QString id, QString key);

		QList<EREssenceData*> list_essences;

		/**
		 * @brief relation_table
		 * Таблица со связями, кардинальности и имена смежных сущностей
		 */
		ERRelationsData relation_table;

};

#endif // DATACONTROLLER_H
