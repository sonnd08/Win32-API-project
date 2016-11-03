using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;

namespace Sprite_UserControl
{
    class _SPRITE_CONTROL
    {
        Bitmap[] _ListImage;
        int _ListSize;
        int _CurrSprite;
        Point _Position;

        public Bitmap[] ListImage
        {
            get
            {
                return _ListImage;
            }

            set
            {
                _ListImage = value;
                _ListSize = _ListImage.Length;
                _CurrSprite = 0;
            }
        }

        public int ListSize
        {
            get
            {
                return _ListSize;
            }

            set
            {
                _ListSize = value;
            }
        }

        public Point Position
        {
            get
            {
                return _Position;
            }

            set
            {
                _Position = value;
            }
        }

        public _SPRITE_CONTROL(Bitmap[] _listImage, Point _position)
        {
            ListImage = _listImage;
            ListSize = _listImage.Count();
            Position = _position;
        }

        public _SPRITE_CONTROL(Bitmap[] _listImage, int _posX, int _posY)
        {
            ListImage = _listImage;
            ListSize = _listImage.Count();
            Point pos = new Point(_posX, _posY);
            Position = pos;
        }

        public int Update()
        {
            _CurrSprite = (_CurrSprite + 1) % _ListSize;
            return 0;
        }

        public int draw(Graphics g)
        {
            g.DrawImage(_ListImage[_CurrSprite], Position);
            Update();
            return 0;
        }
    }
}
