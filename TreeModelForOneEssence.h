#ifndef TREEMODELFORONEESSENCE_H
#define TREEMODELFORONEESSENCE_H


#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <DataController.h>

class TreeItem;

/**
 * @brief The TreeModelForOneEssence class
 *	инкапсулирует модель для представления одной сущности
 */
class TreeModelForOneEssence : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModelForOneEssence(QString id, QObject *parent = 0);
	~TreeModelForOneEssence();

	void update();
	QVariant data(const QModelIndex &index, int role) const Q_DECL_OVERRIDE;
	Qt::ItemFlags flags(const QModelIndex &index) const Q_DECL_OVERRIDE;
	QVariant headerData(int section, Qt::Orientation orientation,
						int role = Qt::DisplayRole) const Q_DECL_OVERRIDE;
	QModelIndex index(int row, int column,
					  const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	QModelIndex parent(const QModelIndex &index) const Q_DECL_OVERRIDE;
	int rowCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;
	int columnCount(const QModelIndex &parent = QModelIndex()) const Q_DECL_OVERRIDE;

private:
	void setupModelData(const QStringList &lines, TreeItem *parent);
	QStringList createLines(QString id);
	TreeItem *rootItem;
};


#endif // TREEMODELFORONEESSENCE_H
