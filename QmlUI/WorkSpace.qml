import QtQuick 2.6

Rectangle {
    id: workSpace
    color: "transparent"
    clip: true

    ListModel {
        id: tilesModel
    }

    function addTile(tile) {
        tile.index = tilesModel.count;
        tilesModel.append({"tile": tile});
        tile.parent = workSpace;
        onTileStateChanged(tile);
        tile.tileStateChanged.connect(onTileStateChanged);
    }

    function removeTile(tile) {
        tilesModel.remove(tile.index);
        tile.destroy();
    }

    function onTileStateChanged(tile) {
        if(tile.state === "Maximize") {
            tile.z = 0;
            for(var i=0; i<tilesModel.count; i++) {
                var item = tilesModel.get(i);
                if(item.tile.index !== tile.index) {
                    item.tile.state = "SmallSize";
                    item.tile.z = 10;
                    tilesModel.set(i, tile);
                }
            }
        } else {
            tile.z = 10;
        }
    }
}
