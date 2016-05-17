#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include <DataController.h>

class TreeItem;

//! [0]
class TreeModel : public QAbstractItemModel
{
	Q_OBJECT

public:
	explicit TreeModel(QObject *parent = 0);
	~TreeModel();

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
	void setupModelData(TreeItem *parent);

	TreeItem *rootItem;
};

#endif // TREEMODEL_H
